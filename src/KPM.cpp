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

#include <Spectra/GenEigsSolver.h>
#include <Spectra/MatOp/SparseGenMatProd.h>
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <Spectra/SymEigsSolver.h>
using namespace Spectra;

//========================================================================================================
double FindEminEmax::findEmin(const sMatrix& hessian)
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder, indexType> op(hessian);
	GenEigsSolver< SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(op, 3, 20);
	// Initialize and compute
	eigs.init();
	eigs.compute(SortRule::SmallestReal, 5000, 0.001);
	// Retrieve results
	if(eigs.info() == CompInfo::Successful)
		evalues = eigs.eigenvalues();
	else
	{
		std::cout << "\nWARNING: Can't calculate Emin: ";
		if( eigs.info() == CompInfo::NotConverging)
			std::cout<<"NOT_CONVERGING\n";
		if( eigs.info() == CompInfo::NumericalIssue)
			std::cout<<"NUMERICAL_ISSUE\n";
		return false;
	}
	//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	return  evalues[0].real();
}

double FindEminEmax::findEmax(const sMatrix& hessian)
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder,indexType> op(hessian);

	// Construct eigen solver object, requesting the largest three eigenvalues
	GenEigsSolver< SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(op, 3, 7);
	// Initialize and compute
	eigs.init();
	eigs.compute(SortRule::LargestMagn);
	// Retrieve results
	if(eigs.info() == CompInfo::Successful)
		evalues = eigs.eigenvalues();
	else
	{
		std::cout << "WARNING: Can't calculate Emax:\n";
		return false;
		//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	}
	return evalues[0].real();
}
//========================================================================================================
//KPM::KPM(): m_params.getR()(100), m_params.getEpsilon()(0.05)
//{
//	setK(100);
//	readCSR();
//}

//KPM::KPM(sMatrix& hessian,  unsigned int K, unsigned int R, float nuEdge, MPI_Comm inworld, string kernel, int lkernel): m_params.getR()(R), m_params.getEpsilon()(nuEdge),m_hessian(hessian), m_world(inworld)
//{
//	setK(K, kernel, lkernel );
//	m_DOF = m_hessian.cols();
//
//	MPI_Comm_params.getR()ank(m_world, &m_mpi_rank);
//	MPI_Comm_size(m_world, &m_mpi_size);
//}
KPM::KPM(sMatrix& hessian, const KPMParams& params, const vector<int>&sizes, const vector<int>&displacements,MPI_Comm inworld):
				m_hessian(hessian), m_params(params), m_world(inworld),
				m_sizes(sizes), m_displacements(displacements)
{
	setK(m_params.getK(), m_params.getKernel(), m_params.getLKernel() );
	m_DOF = m_hessian.cols();

	MPI_Comm_rank(m_world, &m_mpi_rank);
	MPI_Comm_size(m_world, &m_mpi_size);
}


KPM::~KPM() {
	// TODO Auto-generated destructor stub
}


void KPM::constMass(float m)
{
	m_MinvSqrt = 1.0 / sqrt(m) * ones(m_DOF);
//	m_MinvSqrt = Vector::Map(massesFull.data(), massesFull.size());
}
void KPM::setMassVectorInvSqrt( const Vector& mInvSqrt)
{
	m_MinvSqrt = mInvSqrt;

}

void KPM::setEminEmax( const float& emin, const float& emax)
{
	m_params.setEminEmax(emin, emax);
}


float KPM::getEmin() const
{
	return m_params.getEmin();
}
float KPM::getEmax() const
{
	return m_params.getEmax();
}

void KPM::setK(unsigned int K, KPMKernels kernel, int lkernel)
{
	m_params.setK(K);
	//Jackson kernel
	if(kernel == KPMKernels::Jackson)
		jacksonKernel(K);
	if(kernel == KPMKernels::Lorentz)
		lorentzKernel(K, lkernel);
}

void KPM::setR(unsigned int R)
{
	m_params.setR(R);
}

int KPM::getK()
{
	return m_params.getK();
}
int KPM::getR()
{
	return m_params.getR();
}

void KPM::setAF(const Vector& af)
{
	//check if scaled??/
//	FileManager fmanager;
	m_af = m_MinvSqrt.cwiseProduct( af );
//	fmanager.write("m.inv.sqrt.dat", m_MinvSqrt);
//	fmanager.write("af.scaled.dat", m_af);
}

//Rescaling to ~[-1,1] routines
double KPM::aScaling()
{
	return (m_params.getEmax()-m_params.getEmin())/(2.0-m_params.getEpsilon());

}
double KPM::bScaling()
{
	return (m_params.getEmax()+m_params.getEmin())/(2.0);
}
void KPM::ETilde(Vector& e)
{
	if(e.maxCoeff() > m_params.getEmax() || e.minCoeff() < m_params.getEmin())
		processStatus( string("WARNING: Requested output frequencies are not in range of [emin,emax].\n"));
	const double a(aScaling());
	const double  b(bScaling());

	e = (e-b*ones(e.size()))/a;

}
void KPM::HTilde()
{
	double  a = aScaling();
	double  b = bScaling();

	Vector vb = ones(m_hessian.cols())*b;
	sMatrix mb = sMatrix(vb.asDiagonal());

	processStatus( string("Diagonal size: ") + to_string(m_hessian.diagonal().rows()) + string("; non zeros = ") +  to_string(m_hessian.diagonal().nonZeros()) ) ;
//	m_hessian.diagonal(m_displacements[m_mpi_rank]) -= b*ones(m_hessian.rows());//Can cause error if not all diagonal elements exist
//	m_hessian -= ma.block(m_displacements[m_mpi_rank], m_displacements[m_mpi_rank],
//						  m_sizes[m_mpi_rank], m_sizes[m_mpi_rank]);
	m_hessian -= mb.middleRows(m_displacements[m_mpi_rank], m_sizes[m_mpi_rank]);
	m_hessian /= a;
	processStatus( string("Hessian rescale finished"));

	//m_hessian_rank

}

void KPM::jacksonKernel(int K)
{
	Vector n = arange(K);
	m_jk = ((K+1)*ones(n.size())-n);

	m_jk = m_jk.cwiseProduct( cos((c_PI/(K+1))*n));
	m_jk += sin(c_PI*n/(K+1))/tan(c_PI/(K+1)) ;
	m_jk *= (1.0/(K+1));
}
void KPM::lorentzKernel(int K, int parameter )
{
	Vector n = arange(K);
	m_jk = sinh(parameter*(ones(n.size())-n/K))/sinh(parameter);

}
Vector KPM::getCoeffDOS(int chebKind)
{
//	FileManager fmanager;
	Vector loc_gP  = zeros(m_params.getK()); // gauss projection

	int out=0;

	if (!(chebKind == 1 || chebKind == 2))
	{
		processStatus(string("ERROR: chebKind must be 1 or 2" + chebKind));
	}
	Vector v_r = zeros(m_DOF);
	Vector polyChebCurrRank = zeros(m_sizes[m_mpi_rank]);
	for (unsigned int r = 0; r < m_params.getR(); r+=1)
	{
		if (100 * r / m_params.getR() > out )
		{
			processRunningStatus(float(r)/m_params.getR());
			out+=10;
		}

//		Vector v_r = uniform(m_DOF);
		if(m_mpi_rank == 0)
		{
			v_r = normal(m_DOF);
			v_r=v_r/v_r.norm();
		}
		MPI_Bcast(v_r.data(), m_DOF, MPI_DOUBLE, 0, m_world);

//		Vector polyChebCurrRank = v_r;
		Vector polyChebCurr = v_r;
		Vector polyChebPrevPrev = v_r;
		Vector polyChebPrev = v_r;

		loc_gP[0] += v_r.transpose() * polyChebCurr;

		//k = 1
		polyChebCurrRank = chebKind * m_hessian * polyChebPrev;

		MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);

		polyChebPrevPrev = polyChebPrev;
		polyChebPrev = polyChebCurr;

		loc_gP[1] += v_r.transpose() * polyChebCurr;

//		FileManager fmanager;
//		fmanager.write("vr.n."+to_string(m_mpi_size)+"."+ to_string(m_mpi_rank)+".dat", v_r);
//		fmanager.write("pCh.n."+to_string(m_mpi_size)+"."+ to_string(m_mpi_rank)+".dat", polyChebCurrRank);
//		if(m_mpi_rank==0)
//			fmanager.write("vr."+to_string(m_mpi_size)+".Full.dat", v_r);
//		fmanager.write("pCh."+to_string(m_mpi_size)+".Full.dat", polyChebCurr);
//		MPI_Barrier(m_world);
//		std::cout<<"rank: "<<m_mpi_rank<<"; sizes: ";
//		for(int i:m_displacements)
//			std::cout<<i<<" ";
//		std::cout<<endl;
//		std::cout.flush();
//		return loc_gP;

		for (unsigned int k = 2; k < m_params.getK(); ++k)
		{

			polyChebCurrRank = 2 * m_hessian * polyChebPrev;
			MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);

//			if (k==20)
//			{
//				FileManager fmanager;
//				fmanager.write("vr.n."+to_string(m_mpi_size)+"."+ to_string(m_mpi_rank)+".dat", v_r);
//				fmanager.write("pCh.n."+to_string(m_mpi_size)+"."+ to_string(m_mpi_rank)+".dat", polyChebCurrRank);
//				if(m_mpi_rank==0)
//					fmanager.write("vr."+to_string(m_mpi_size)+".Full.dat", v_r);
//					fmanager.write("pCh."+to_string(m_mpi_size)+".Full.dat", polyChebCurr);
//				MPI_Barrier(m_world);
//				return loc_gP;
//			}
			polyChebCurr = polyChebCurr - polyChebPrevPrev;
			loc_gP[k] += v_r.transpose() * polyChebCurr;
			polyChebPrevPrev = polyChebPrev;
			polyChebPrev = polyChebCurr;

		}
	}
	processRunningStatus(1.0f);
	processEnded();
//	MPI_Reduce(loc_gP.data(), glob_gP.data(), m_params.getK(), MPI_DOUBLE, MPI_SUM, 0, m_world);
	return loc_gP;
}
//Vector KPM::getCoeffDOS(int chebKind)
//{
////	FileManager fmanager;
//	Vector loc_gP  = zeros(m_params.getK()); // gauss projection
//	Vector glob_gP = zeros(m_params.getK()); // gauss projection
//
//	int out=0;
//
//	if (!(chebKind == 1 || chebKind == 2))
//	{
//		processStatus(string("ERROR: chebKind must be 1 or 2" + chebKind));
//	}
//	for (unsigned int r = m_mpi_rank; r < m_params.getR(); r+=m_mpi_size)
//	{
//		if (100 * r / m_params.getR() > out )
//		{
//			processRunningStatus(float(r)/m_params.getR());
//			out+=10;
//		}
//
////		Vector v_r = uniform(m_DOF);
//		Vector v_r = normal(m_DOF);
//		v_r=v_r/v_r.norm();
//		if (r<2)
//		{
////			fmanager.write("u"+to_string(r), v_r);
//		}
//		Vector polyChebCurr = v_r;
//		Vector polyChebPrevPrev = v_r;
//		Vector polyChebPrev = v_r;
//
//		loc_gP[0] += v_r.transpose() * polyChebCurr;
//
//		//k = 1
//		polyChebCurr = chebKind * m_hessian * polyChebPrev;
//		polyChebPrevPrev = polyChebPrev;
//		polyChebPrev = polyChebCurr;
//
//		loc_gP[1] += v_r.transpose() * polyChebCurr;
//
//		for (unsigned int k = 2; k < m_params.getK(); ++k)
//		{
//
//			polyChebCurr = 2 * m_hessian * polyChebPrev - polyChebPrevPrev;
//			loc_gP[k] += v_r.transpose() * polyChebCurr;
//			polyChebPrevPrev = polyChebPrev;
//			polyChebPrev = polyChebCurr;
//
//
//		}
//	}
//	processEnded();
//	MPI_Reduce(loc_gP.data(), glob_gP.data(), m_params.getK(), MPI_DOUBLE, MPI_SUM, 0, m_world);
//	return glob_gP;
//}

Vector KPM::getCoeffGammaDOS()
{

	Vector loc_gP  = zeros(m_params.getK()); // gauss projection


	if(m_mpi_rank==0)
		cout <<"MPI size:"<< m_mpi_size<<endl;
	Vector v_r = zeros(m_DOF);
	int out=0;
	for (unsigned int r = 0; r < m_params.getR(); r+=1)
	{
		if (100 * r / m_params.getR() > out)
		{
			processRunningStatus(float(r)/m_params.getR());
			out+=10;
//			if(m_mpi_rank == 0)
//			fmanager.write("gPgamma.c"+to_string(rank)+"_K"+to_string(m_params.getK())+"_R" +to_string(int(r/m_mpi_size)) + ".dat",loc_gP);
		}

		if(m_mpi_rank == 0)
		{
			v_r = normal(m_DOF);
			v_r=v_r/v_r.norm();
		}
		MPI_Bcast(v_r.data(), m_DOF, MPI_DOUBLE, 0, m_world);

		double mLeft = m_af.dot(v_r);

		Vector polyChebCurrRank = v_r;
		Vector polyChebCurr = v_r;
		Vector polyChebPrevPrev = v_r;
		Vector polyChebPrev = v_r;

		loc_gP[0] += mLeft * mLeft;

		//k = 1
		polyChebCurrRank = 2.0 * m_hessian * polyChebPrev ;
		MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);
		polyChebPrevPrev = polyChebPrev;
		polyChebPrev = polyChebCurr;

		loc_gP[1] += mLeft * m_af.dot( polyChebCurr);

		for (unsigned int k = 2; k < m_params.getK(); ++k)
		{
			polyChebCurrRank = 2 * m_hessian * polyChebPrev;
			MPI_Allgatherv( polyChebCurrRank.data(), polyChebCurrRank.size(), MPI_DOUBLE, polyChebCurr.data(), m_sizes.data(), m_displacements.data(), MPI_DOUBLE,  m_world);
			polyChebCurr = polyChebCurr - polyChebPrevPrev;
			polyChebPrevPrev = polyChebPrev;
			polyChebPrev = polyChebCurr;

			loc_gP[k] += mLeft * m_af.dot( polyChebCurr);
		}
	}
	processRunningStatus(1.0f);
	processEnded();
//	MPI_Reduce(loc_gP.data(), glob_gP.data(), m_params.getK(), MPI_DOUBLE, MPI_SUM, 0, m_world);
	return loc_gP;
}



Vector KPM::sumSeries(const Vector& freq, const Vector& gP, int chebKind)
{
	Vector sumKPM = zeros(freq.size());
	Vector e = sign(freq).cwiseProduct(sqr(freq));
	ETilde(e);
	Vector	arccosArgument	= arccos(e);
	Vector 	prefactor = ones(freq.size());
	//Vector 	prefactor		= 4*abs(freq)*abs((2.0-m_params.getEpsilon())/c_PI/(m_params.getEmax()-m_params.getEmin()));
	if(chebKind == 2)
	{
		prefactor  = 4*abs(freq)*abs((2.0-m_params.getEpsilon())/c_PI/(m_params.getEmax()-m_params.getEmin()));
//		prefactor  = 4*sqrt(sqr(freq)+pow(c_PI/m_params.getK()/2, 2)*m_params.getEmax()*ones(freq.size())) * abs((2.0-m_params.getEpsilon())/c_PI/(m_params.getEmax()-m_params.getEmin()));

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
			sumKPM			+= prefactor.cwiseProduct(( m_jk[k]*gP[k]/m_params.getR())  * sin((k + 1.0) * arccosArgument));
		else
			sumKPM			+= cof*prefactor.cwiseProduct(( m_jk[k]*gP[k]/m_params.getR())  * cos((k) * arccosArgument));

		cof = 2;
	}
	return sumKPM;
}

Vector KPM::getModulus(const float& GA, const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq, float nu )
{
	cout<<"Modulus calculation....\n GA: "<<GA<<"\tVolume: "<<volume<<"\tDOF: "<<m_DOF<<endl;

	Vector Gp = zeros(gdos_freq.size());
	Vector e = sign(gdos_freq).cwiseProduct(sqr(gdos_freq));
	int vsize = e.size();
	for( int i = 0; i < freq.size();++i)
	{
			Vector ediff = e - ones(vsize) * freq[i] * freq[i];

			Vector denom = ((sqr(ediff) + ones(vsize)*(nu * freq[i])*(nu * freq[i])) * volume / m_DOF).cwiseInverse();
;
			Gp[i] = GA - trapz(gdos.cwiseProduct(ediff).cwiseProduct(denom), gdos_freq);
 	}

	return Gp;
}

Vector KPM::getModulusImag(const float& GA, const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq, float nu )
{
	cout<<"Modulus calculation....\n GA: "<<GA<<"\tVolume: "<<volume<<"\tDOF: "<<m_DOF<<endl;

//	float volume = 571.0;
//	float N = m_DOF/3.0;

	Vector Gpp = zeros(gdos_freq.size());
	Vector e = sign(gdos_freq).cwiseProduct(sqr(gdos_freq));

	int vsize = e.size();
	for( int i = 0; i < freq.size();++i)
	{
			Vector ediff = e - ones(vsize) * freq[i] * freq[i];
			Vector denom = ((sqr(ediff) + ones(vsize)*(nu * freq[i])*(nu * freq[i])) * volume / m_DOF).cwiseInverse();
			Gpp[i] = trapz((gdos * freq[i] * nu).cwiseProduct(denom), gdos_freq);
 	}

	return Gpp;
}

//Vector KPM::getKArray(float dfreq)
//{
//	processStatus("L");
////	FileManager fmanager;
//	int L = (sqrt(m_params.getEmax()) +sqrt(-m_params.getEmin()))/dfreq;
//	processStatus("freq");
//	Vector freq = arange(L,-sqrt(abs(m_params.getEmin())), sqrt(m_params.getEmax()));
////	fmanager.write("K.array.freq.dat", freq);
//	processStatus("a");
//	float a = (c_PI/(2.0*(m_params.getEmax() - m_params.getEmin())*dfreq));
////	fmanager.write("K.array.a.dat", a);
//	processStatus("b");
//	Vector b = pow(2-m_params.getEpsilon(), 2)*sqr(2.0*freq-ones(freq.size())*(m_params.getEmax() + m_params.getEmin()));
////	fmanager.write("K.array.b.dat", b);
//	processStatus("c");
//	Vector c = pow(m_params.getEmax() - m_params.getEmin(),2)*ones(freq.size());
////	fmanager.write("K.array.c.dat", c);
//	processStatus("return");
//	return  a * sqrt( c - b );
//}
//Vector KPM::getKArray(const Vector& freq)
//{
////	return (m_params.getEmax()-m_params.getEmin())*freq.cwiseInverse()/2/m_DOF;
//	int Kmin = 250;
//	return (m_params.getEmax()-m_params.getEmin())*abs(freq.cwiseInverse())/2/6000 + Kmin*ones(freq.size());// /m_DOF
//}
//Vector KPM::getSpreading(Vector freq)
//{
//	return (c_PI/(2.0*(m_params.getEmax() - m_params.getEmin())*m_params.getK())) * sqrt(pow(m_params.getEmax() - m_params.getEmin(),2)*ones(freq.size()) - pow(2-m_params.getEpsilon(), 2)*sqr(2.0*freq-ones(freq.size())*(m_params.getEmax() + m_params.getEmin())));
//}
