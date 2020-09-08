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


//KPM::KPM(): m_R(100), m_nuEdge(0.05)
//{
//	setK(100);
//	readCSR();
//}

KPM::KPM(sMatrix& hessian,  unsigned int K, unsigned int R, float nuEdge): m_R(R), m_nuEdge(nuEdge),m_hessian(hessian)
{
	setK(K);
	std::cout<<"KPM constructor..."<<"mem: " << mem()<<std::endl;
	m_DOF = m_hessian.cols();
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

void KPM::findEmin()
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder, indexType> op(m_hessian);
	GenEigsSolver< double, SMALLEST_REAL, SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(&op, 3, 7);
	// Initialize and compute
	eigs.init();
	eigs.compute();
	// Retrieve results
	if(eigs.info() == SUCCESSFUL)
		evalues = eigs.eigenvalues();
	else
		std::cout << "\nWARNING: Can't calculate Emin:\n";
	//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	m_emin = evalues[0].real();
}

void KPM::findEmax()
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder,indexType> op(m_hessian);

	// Construct eigen solver object, requesting the largest three eigenvalues
	GenEigsSolver< double, LARGEST_MAGN, SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(&op, 3, 7);
	// Initialize and compute
	eigs.init();
	eigs.compute();
	// Retrieve results
	if(eigs.info() == SUCCESSFUL)
		evalues = eigs.eigenvalues();
	else
		std::cout << "WARNING: Can't calculate Emax:\n";

	//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	m_emax = evalues[0].real();
}

void KPM::setEmin( const float& emin)
{
	m_emin = emin;
}

void KPM::setEmax( const float& emax)
{
	m_emax = emax;
}

float KPM::getEmin() const
{
	return m_emin;
}
float KPM::getEmax() const
{
	return m_emax;
}

void KPM::setK(unsigned int K)
{
	m_K = K;
	jacksonKernel(K);
}

void KPM::setR(unsigned int R)
{
	m_R = R;
}

int KPM::getK()
{
	return m_K;
}
int KPM::getR()
{
	return m_R;
}

void KPM::setAF(const Vector& af)
{
	//check if scaled??/
	m_af = m_MinvSqrt.cwiseProduct( af );
}

//Rescaling to ~[-1,1] routines
double KPM::aScaling()
{
	return (m_emax-m_emin)/(2.0-m_nuEdge);

}
double KPM::bScaling()
{
	return (m_emax+m_emin)/(2.0);
}
void KPM::ETilde(Vector& e)
{
	if(e.maxCoeff() > m_emax || e.minCoeff() < m_emin)
		std::cout << "WARNING: Requested output frequencies are not in range of [emin,emax].\n";
	const double a(aScaling());
	const double  b(bScaling());

	e = (e-b*ones(e.size()))/a;

}
void KPM::HTilde()
{
	double  a = aScaling();
	double  b = bScaling();

	std::cout<<"Diagonal size: "<<m_hessian.diagonal().rows()<<"; non zeros = "<< m_hessian.diagonal().nonZeros()<<std::endl;
//	m_hessian.diagonal() -= b*ones(m_hessian.rows());
//	m_hessian /= a;
	for (int i =0; i < m_hessian.rows(); ++i)
	{
		m_hessian.coeffRef(i,i) -= b;
		m_hessian.coeffRef(i,i) /= a;
		if(i==1000)
			std::cout<<i<<std::endl;
	}
}

void KPM::jacksonKernel(int K)
{
	Vector n = arange(K);
	m_jk = ((K+1)*ones(n.size())-n);

	m_jk = m_jk.cwiseProduct( cos((c_PI/(K+1))*n));
	m_jk += sin(c_PI*n/(K+1))/tan(c_PI/(K+1)) ;
	m_jk *= (1.0/(K+1));
}


Vector KPM::getCoeffDOS()
{
	Vector loc_gP = zeros(m_K); // gauss projection
	Vector glob_gP = zeros(m_K); // gauss projection
	int rank = MPI::COMM_WORLD.Get_rank();
	int size = MPI::COMM_WORLD.Get_size();

	for (int r = rank; r < m_R; r+=size)
	{
		if (r % 10 == 0)
			processRunningStatus(float(r)/m_R);

		Vector v_r = normal(m_DOF);
		v_r=v_r/v_r.norm();
		Vector polyChebCurr = v_r;
		Vector polyChebPrevPrev = v_r;
		Vector polyChebPrev = v_r;

		loc_gP[0] += v_r.transpose() * polyChebCurr;

		//k = 1
		polyChebCurr = 2 * m_hessian * polyChebPrev;
		polyChebPrevPrev = polyChebPrev;
		polyChebPrev = polyChebCurr;

		loc_gP[1] += v_r.transpose() * polyChebCurr;

		for (int k = 2; k < m_K; ++k)
		{

			polyChebCurr = 2 * m_hessian * polyChebPrev - polyChebPrevPrev;
			loc_gP[k] += v_r.transpose() * polyChebCurr;
			polyChebPrevPrev = polyChebPrev;
			polyChebPrev = polyChebCurr;


		}
	}
	processEnded();
	MPI::COMM_WORLD.Reduce(loc_gP.data(), glob_gP.data(), m_K, MPI::DOUBLE, MPI::SUM, 0);
	return glob_gP;
}

Vector KPM::getCoeffGammaDOS()
{
	FileManager fmanager;
	Vector loc_gP = zeros(m_K); // gauss projection
	Vector glob_gP = zeros(m_K); // gauss projection

	int rank = MPI::COMM_WORLD.Get_rank();
	int size = MPI::COMM_WORLD.Get_size();
	cout <<"MPI size:"<< size<<endl;
	for (int r = rank; r < m_R; r+=size)
	{
		if (r % 100 == 0)
		{
			processRunningStatus(float(r)/m_R);
			if(rank == 0)
				fmanager.write("gPgamma_K"+to_string(m_K)+"_R" +to_string(int(r/size)) + ".dat",loc_gP);
		}

		Vector v_r = normal(m_DOF);
		v_r=v_r/v_r.norm();
		if(r < 8)
			fmanager.write("u"+to_string(r)+"c"+to_string(size)+".dat", v_r);

		double mLeft = m_af.dot(v_r);

		Vector polyChebCurr = v_r;
		Vector polyChebPrevPrev = v_r;
		Vector polyChebPrev = v_r;

		loc_gP[0] += mLeft * mLeft;

		//k = 1
		polyChebCurr = 2.0 * m_hessian * v_r ;
		polyChebPrevPrev = v_r;
		polyChebPrev = polyChebCurr;

		loc_gP[1] += mLeft * m_af.dot( polyChebCurr);

		for (int k = 2; k < m_K; ++k)
		{

			polyChebCurr = 2.0 * m_hessian * polyChebPrev  - polyChebPrevPrev;
			polyChebPrevPrev = polyChebPrev;
			polyChebPrev = polyChebCurr;

			loc_gP[k] += mLeft * m_af.dot( polyChebCurr);
		}
	}
	processEnded();
	MPI::COMM_WORLD.Reduce(loc_gP.data(), glob_gP.data(), m_K, MPI::DOUBLE, MPI::SUM, 0);
	cout<<"rank: "<<rank<<". loc: "<<loc_gP[0]<<". glob: "<<glob_gP[0]<<endl;
	return glob_gP;
}

Vector KPM::sumSeries(const Vector& freq, const Vector& gP)
{
	Vector sumKPM = zeros(freq.size());
	Vector e = sign(freq).cwiseProduct(sqr(freq));
	ETilde(e);
	Vector	arccosArgument	= arccos(e);
	Vector 	prefactor		= 4*abs(freq)*abs((2.0-m_nuEdge)/c_PI/(m_emax-m_emin));

	for ( int k =0; k < m_K; ++k)
	{

		sumKPM			+= prefactor.cwiseProduct(( m_jk[k]*gP[k]/m_R)  * sin((k + 1.0) * arccosArgument));

	}
	return sumKPM;
}

Vector KPM::getModulus(const float& GA, const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq )
{
	cout<<"Modulus calculation....\n GA: "<<GA<<"\tVolume: "<<volume<<endl;
	float nu = 1.0;
//	float volume = 571.0;
//	float N = m_DOF/3.0;

	Vector Gp = zeros(gdos_freq.size());
	Vector e = sign(gdos_freq).cwiseProduct(sqr(gdos_freq));

	int vsize = e.size();
	for( int i = 0; i < freq.size();++i)
	{
			Vector ediff = e - ones(vsize) * freq[i] * freq[i];
			Vector denom = ((sqr(ediff) + ones(vsize)*(nu * freq[i])*(nu * freq[i])) * volume / m_DOF).cwiseInverse();
			Gp[i] = GA - trapz(gdos.cwiseProduct(ediff).cwiseProduct(denom), gdos_freq);
 	}

	return Gp;
}

Vector KPM::getModulusImag(const float& GA, const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq )
{
	cout<<"Modulus calculation....\n GA: "<<GA<<"\tVolume: "<<volume<<endl;
	float nu = 1.0;
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

//Vector gp_gpp(n_bins_0, bin_min, bin_max, GA, GammaDos, nu, Volume, N):
//    n_bins = int(n_bins_0);
//    bin_width = (bin_max - bin_min) / n_bins
//    # print bin_min
//
//    Gp = np.zeros(shape=(n_bins, 2))
//    Gpp = np.zeros(shape=(n_bins, 2))
//
//    E = np.sign(GammaDos[0]) * (GammaDos[0]) ** 2
//    # E = (GammaDos[0]) ** 2
//    for i in range(n_bins):
//        freq = 10.0 ** (bin_min + i * bin_width)
//        Ediff = (E - freq ** 2)
//        denom = (Ediff ** 2 + (nu * freq) ** 2) * Volume / 3.0 / N
//
//        Gp[i][1] = GA - np.trapz(GammaDos[1] * Ediff / denom, GammaDos[0])
//        Gpp[i][1] = np.trapz(GammaDos[1] * freq * nu / denom, GammaDos[0])
//        Gp[i][0] = freq
//        Gpp[i][0] = freq
//
//    return Gp, Gpp

