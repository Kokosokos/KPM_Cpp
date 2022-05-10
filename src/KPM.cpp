/*
 * KPM.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ivan
 */

//To read lammps data file
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>


#include "KPM.h"
#include <Eigen/Core>
#include <Eigen/SparseCore>
//========================================================================================================

KPM::KPM(sMatrixPointer hessian, const KPMParams& params, const vector<int>&sizes, const vector<int>&displacements,MPI_Comm inworld):
				m_hessian(std::move(hessian)), m_params(params), m_world(inworld),
				m_sizes(sizes), m_displacements(displacements)
{
	MPI_Comm_rank(m_world, &m_mpi_rank);
	MPI_Comm_size(m_world, &m_mpi_size);
	m_DOF = m_hessian->cols();
	HTilde();
}
KPM::KPM(const KPMParams& params, const Vector& gp):m_params(params), m_gp(gp)
{
}

void KPM::calculateCoefficients(int chebKind)
{
	processStatus("Base class getCoefficients");
}
//-------------------------------------------------------------------------------

//Rescaling to ~[-1,1] routines
double KPM::aScaling()
{
	return (m_params.getEmax()-m_params.getEmin())/(2.0-m_params.getEpsilon());

}
//-------------------------------------------------------------------------------

double KPM::bScaling()
{
	return (m_params.getEmax()+m_params.getEmin())/(2.0);
}
//-------------------------------------------------------------------------------

void KPM::ETilde(Vector& e)
{
	if(e.maxCoeff() > m_params.getEmax() || e.minCoeff() < m_params.getEmin())
		processStatus( string("WARNING: Requested output frequencies are not in range of [emin,emax].\n"));
	const double a(aScaling());
	const double  b(bScaling());

	e = (e-b*ones(e.size()))/a;

}
//-------------------------------------------------------------------------------

void KPM::HTilde()
{
	double  a = aScaling();
	double  b = bScaling();

	Vector vb = ones(m_hessian->cols())*b;
	sMatrix mb = sMatrix(vb.asDiagonal());

	processStatus( string("Diagonal size: ") + to_string(m_hessian->diagonal().rows()) + string("; non zeros = ") +  to_string(m_hessian->diagonal().nonZeros()) ) ;

	*m_hessian -= mb.middleRows(m_displacements[m_mpi_rank], m_sizes[m_mpi_rank]);
	*m_hessian /= a;
	processStatus( string("Hessian rescale finished"));

	//m_hessian_rank

}
//-------------------------------------------------------------------------------

Vector KPM::sumSeries(const Vector& freq, int chebKind)
{
	processStatus("Sum 1");
	Vector sumKPM = zeros(freq.size());
	Vector e = sign(freq).cwiseProduct(sqr(freq));
	processStatus("Sum 2");
	processStatus("Sum 3 "  +  std::to_string(m_params.K));
	processStatus("Sum 3 "  +  std::to_string(m_params.R)   );
	processStatus("Sum 3 " +  std::to_string(m_params.density)   );

	ETilde(e);
	processStatus("Sum 4");
	Vector	arccosArgument	= arccos(e);
	processStatus("Sum 5");
	Vector 	prefactor = ones(freq.size());
	processStatus("Sum 6");
	if(chebKind == 2)
	{
		prefactor  = 4*abs(freq)*abs((2.0-m_params.getEpsilon())/c_PI/(m_params.getEmax()-m_params.getEmin()));
	}
	else
	{
		prefactor  =  2*abs(freq)*abs((2.0-m_params.getEpsilon())/c_PI/(m_params.getEmax()-m_params.getEmin()));
		prefactor = prefactor.cwiseProduct( (sqrt(ones(e.size()) - sqr(e))).cwiseInverse() );
	}
	int cof = 1;

	for ( unsigned int k =0; k < m_params.getK(); ++k)
	{
		if(chebKind == 2)
			sumKPM			+= prefactor.cwiseProduct(( m_params.m_jk[k]*m_gp[k]/m_params.getR())  * sin((k + 1.0) * arccosArgument));
		else
			sumKPM			+= cof*prefactor.cwiseProduct(( m_params.m_jk[k]*m_gp[k]/m_params.getR())  * cos((k) * arccosArgument));

		cof = 2;
	}
	return sumKPM;
}
//========================================================================================================
KPMDOS::KPMDOS(sMatrixPointer hessian, const KPMParams& params, const vector<int>&sizes, const vector<int>&displacements,MPI_Comm inworld):
				KPM(std::move(hessian), params,sizes, displacements,inworld)
{
	calculateCoefficients();
}

void KPMDOS::calculateCoefficients(int chebKind)
{
	processStatus("KPMDOS class getCoefficients");
	if (!(chebKind == 1 || chebKind == 2))
	{
		processStatus(string("ERROR: chebKind must be 1 or 2" + chebKind));
	}
	Vector loc_gP  = zeros(m_params.getK()); // gauss projection
	Vector polyChebCurrRank = zeros(m_sizes[m_mpi_rank]);
	Vector v_r = zeros(m_DOF);
	unsigned int out=0;
	for (unsigned int r = 0; r < m_params.getR(); r+=1)
	{
		if (100 * r / m_params.getR() > out )
		{
			processRunningStatus(float(r)/m_params.getR());
			out+=10;
		}

		if(m_mpi_rank == 0)
		{
			v_r = normal(m_DOF);
			v_r=v_r/v_r.norm();
		}
		MPI_Bcast(v_r.data(), m_DOF, MPI_DOUBLE, 0, m_world);

		Vector polyChebCurr = v_r;
		Vector polyChebPrevPrev = v_r;
		Vector polyChebPrev = v_r;

		loc_gP[0] += v_r.transpose() * polyChebCurr;

		//k = 1
		polyChebCurrRank = chebKind * (*m_hessian) * polyChebPrev;
		MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);
		polyChebPrevPrev = polyChebPrev;
		polyChebPrev = polyChebCurr;

		loc_gP[1] += v_r.transpose() * polyChebCurr;


		for (unsigned int k = 2; k < m_params.getK(); ++k)
		{

			polyChebCurrRank = 2 * (*m_hessian) * polyChebPrev;
			MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);
			polyChebCurr = polyChebCurr - polyChebPrevPrev;
			loc_gP[k] += v_r.transpose() * polyChebCurr;
			polyChebPrevPrev = polyChebPrev;
			polyChebPrev = polyChebCurr;

		}
	}
	processRunningStatus(1.0f);
	processEnded();
	m_gp = loc_gP;
}

const Vector& KPM::getCoefficients() const {
	return m_gp;
}
//========================================================================================================

//-------------------------------------------------------------------------------
KPMGammaDOS::KPMGammaDOS(sMatrixPointer hessian, const KPMParams& params, const vector<int>&sizes, const vector<int>&displacements,MPI_Comm inworld):
				KPM(std::move(hessian), params,sizes, displacements,inworld)
{
	calculateCoefficients();
}
void KPMGammaDOS::calculateCoefficients(int chebKind)
{
	processStatus("KPMGammaDOS class getCoefficients");
	if (!(chebKind == 1 || chebKind == 2))
	{
		processStatus(string("ERROR: chebKind must be 1 or 2" + chebKind));
	}
	Vector loc_gP  = zeros(m_params.getK()); // gauss projection
	Vector v_r = zeros(m_DOF);
	unsigned int out=0;
	for (unsigned int r = 0; r < m_params.getR(); r+=1)
	{
		if (100 * r / m_params.getR() > out)
		{
			processRunningStatus(float(r)/m_params.getR());
			out+=10;
		}

		if(m_mpi_rank == 0)
		{
			v_r = normal(m_DOF);
			v_r=v_r/v_r.norm();
		}
		MPI_Bcast(v_r.data(), m_DOF, MPI_DOUBLE, 0, m_world);

		Vector polyChebCurrRank = v_r;
		Vector polyChebCurr = v_r;
		Vector polyChebPrevPrev = v_r;
		Vector polyChebPrev = v_r;

		double mLeft = m_params.af.dot(v_r);
		loc_gP[0] += mLeft * mLeft;

		//k = 1
		polyChebCurrRank = 2.0 * (*m_hessian) * polyChebPrev ;
		MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);
		polyChebPrevPrev = polyChebPrev;
		polyChebPrev = polyChebCurr;

		loc_gP[1] += mLeft * m_params.af.dot( polyChebCurr);

		for (unsigned int k = 2; k < m_params.getK(); ++k)
		{
			polyChebCurrRank = 2 * (*m_hessian) * polyChebPrev;
			MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);
			polyChebCurr = polyChebCurr - polyChebPrevPrev;
			polyChebPrevPrev = polyChebPrev;
			polyChebPrev = polyChebCurr;

			loc_gP[k] += mLeft * m_params.af.dot( polyChebCurr);
		}
	}
	processRunningStatus(1.0f);
	processEnded();
	m_gp = loc_gP;
}


Vector ShearModulus::getStorage(KPMGParams params,  const Vector& gdos_freq, const Vector& gdos, const Vector& freq)
{
	Vector Gp = zeros(gdos_freq.size());
	Vector e = sign(gdos_freq).cwiseProduct(sqr(gdos_freq));
	int vsize = e.size();
	for( int i = 0; i < freq.size();++i)
	{
			Vector ediff = e - ones(vsize) * freq[i] * freq[i];

			Vector denom = ((sqr(ediff) + ones(vsize)*(params.nu * freq[i])*(params.nu * freq[i])) * params.density / 3.0 ).cwiseInverse();
;
			Gp[i] = params.GA - trapz(gdos.cwiseProduct(ediff).cwiseProduct(denom), gdos_freq);
 	}

	return Gp;
}

Vector ShearModulus::getLoss(KPMGParams params,  const Vector& gdos_freq, const Vector& gdos, const Vector& freq)
{

	Vector Gpp = zeros(gdos_freq.size());
	Vector e = sign(gdos_freq).cwiseProduct(sqr(gdos_freq));

	int vsize = e.size();
	for( int i = 0; i < freq.size();++i)
	{
			Vector ediff = e - ones(vsize) * freq[i] * freq[i];
			Vector denom = ((sqr(ediff) + ones(vsize)*(params.nu * freq[i])*(params.nu * freq[i])) * params.density / 3.0).cwiseInverse();
			Gpp[i] = trapz((gdos * freq[i] * params.nu).cwiseProduct(denom), gdos_freq);
 	}

	return Gpp;
}

