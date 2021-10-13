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

KPM::KPM(sMatrix& hessian,  unsigned int K, unsigned int R, float nuEdge, MPI_Comm inworld, string kernel, int lkernel): m_R(R), m_nuEdge(nuEdge),m_hessian(hessian), m_world(inworld)
{
	setK(K, kernel, lkernel );
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

bool KPM::findEmin()
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder, indexType> op(m_hessian);
	GenEigsSolver< double, SMALLEST_REAL, SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(&op, 3, 20);
	// Initialize and compute
	eigs.init();
	eigs.compute(5000, 0.001, SMALLEST_REAL);
	// Retrieve results
	if(eigs.info() == SUCCESSFUL)
		evalues = eigs.eigenvalues();
	else
	{
		std::cout << "\nWARNING: Can't calculate Emin: ";
		if( eigs.info() == NOT_CONVERGING)
			std::cout<<"NOT_CONVERGING\n";
		if( eigs.info() == NUMERICAL_ISSUE)
			std::cout<<"NUMERICAL_ISSUE\n";
		return false;
	}
	//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	m_emin = evalues[0].real();
	return true;
}

bool KPM::findEmax()
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
	{
		std::cout << "WARNING: Can't calculate Emax:\n";
		return false;
		//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	}
	m_emax = evalues[0].real();
	return true;
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

void KPM::setK(unsigned int K, string kernel, int lkernel)
{
	m_K = K;
	//Jackson kernel
	if(kernel == "jk")
		jacksonKernel(K);
	if(kernel == "lk")
		lorentzKernel(K, lkernel);
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
	FileManager fmanager;
	m_af = m_MinvSqrt.cwiseProduct( af );
	fmanager.write("m.inv.sqrt.dat", m_MinvSqrt);
	fmanager.write("af.scaled.dat", m_af);
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
		processStatus( string("WARNING: Requested output frequencies are not in range of [emin,emax].\n"));
	const double a(aScaling());
	const double  b(bScaling());

	e = (e-b*ones(e.size()))/a;

}
void KPM::HTilde()
{
	double  a = aScaling();
	double  b = bScaling();

	processStatus( string("Diagonal size: ") + to_string(m_hessian.diagonal().rows()) + string("; non zeros = ") +  to_string(m_hessian.diagonal().nonZeros()) ) ;
	m_hessian.diagonal() -= b*ones(m_hessian.rows());//Can cause error if not all diagonal elements exist
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

//def jacksonKernel(n,N):
//	jK_func=1.0/(N+1) * ((N-n+1)*np.cos(np.pi*n/(N+1)) + np.sin(np.pi*n/(N+1))/np.tan(np.pi/(N+1)))
//	return jK_func
//
//def lorentzKernel(n,N,parameter):
//	lK_func=np.sinh(parameter*(1-n/N))/np.sinh(parameter)
//	return lK_func

Vector KPM::getCoeffDOS(int chebKind)
{
//	FileManager fmanager;
	Vector loc_gP = zeros(m_K); // gauss projection
	Vector glob_gP = zeros(m_K); // gauss projection

	int out=0;

	if (!(chebKind == 1 || chebKind == 2))
	{
		processStatus(string("ERROR: chebKind must be 1 or 2" + chebKind));
	}
	for (int r = m_mpi_rank; r < m_R; r+=m_mpi_size)
	{
		if (100 * r / m_R > out )
		{
			processRunningStatus(float(r)/m_R);
			out+=10;
		}

//		Vector v_r = uniform(m_DOF);
		Vector v_r = normal(m_DOF);
		v_r=v_r/v_r.norm();
		if (r<2)
		{
//			fmanager.write("u"+to_string(r), v_r);
		}
		Vector polyChebCurr = v_r;
		Vector polyChebPrevPrev = v_r;
		Vector polyChebPrev = v_r;

		loc_gP[0] += v_r.transpose() * polyChebCurr;

		//k = 1
		polyChebCurr = chebKind * m_hessian * polyChebPrev;
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
	MPI_Reduce(loc_gP.data(), glob_gP.data(), m_K, MPI_DOUBLE, MPI_SUM, 0, m_world);
	return glob_gP;
}

Vector KPM::getCoeffGammaDOS()
{
//	FileManager fmanager;
	Vector loc_gP = zeros(m_K); // gauss projection
	Vector glob_gP = zeros(m_K); // gauss projection


	if(m_mpi_rank==0)
		cout <<"MPI size:"<< m_mpi_size<<endl;
	for (int r = m_mpi_rank; r < m_R; r+=m_mpi_size)
	{
		if (r % 100 < m_mpi_size )
		{
			processRunningStatus(float(r)/m_R);
//			if(m_mpi_rank == 0)
//			fmanager.write("gPgamma.c"+to_string(rank)+"_K"+to_string(m_K)+"_R" +to_string(int(r/m_mpi_size)) + ".dat",loc_gP);
		}

		Vector v_r = normal(m_DOF);
		v_r=v_r/v_r.norm();
//		if(r < 8)
//			fmanager.write("u"+to_string(r)+"c"+to_string(m_mpi_size)+".dat", v_r);

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
	MPI_Reduce(loc_gP.data(), glob_gP.data(), m_K, MPI_DOUBLE, MPI_SUM, 0, m_world);
	cout<<"rank: "<<m_mpi_rank<<". loc: "<<loc_gP[0]<<". glob: "<<glob_gP[0]<<endl;
	return glob_gP;
}

Vector KPM::getKArray(float dfreq)
{
	processStatus("L");
//	FileManager fmanager;
	int L = (sqrt(m_emax) +sqrt(-m_emin))/dfreq;
	processStatus("freq");
	Vector freq = arange(L,-sqrt(abs(m_emin)), sqrt(m_emax));
//	fmanager.write("K.array.freq.dat", freq);
	processStatus("a");
	float a = (c_PI/(2.0*(m_emax - m_emin)*dfreq));
//	fmanager.write("K.array.a.dat", a);
	processStatus("b");
	Vector b = pow(2-m_nuEdge, 2)*sqr(2.0*freq-ones(freq.size())*(m_emax + m_emin));
//	fmanager.write("K.array.b.dat", b);
	processStatus("c");
	Vector c = pow(m_emax - m_emin,2)*ones(freq.size());
//	fmanager.write("K.array.c.dat", c);
	processStatus("return");
	return  a * sqrt( c - b );
}
Vector KPM::getKArray(const Vector& freq)
{
//	return (m_emax-m_emin)*freq.cwiseInverse()/2/m_DOF;
	int Kmin = 250;
	return (m_emax-m_emin)*abs(freq.cwiseInverse())/2/6000 + Kmin*ones(freq.size());// /m_DOF
}
Vector KPM::getSpreading(Vector freq)
{
	return (c_PI/(2.0*(m_emax - m_emin)*m_K)) * sqrt(pow(m_emax - m_emin,2)*ones(freq.size()) - pow(2-m_nuEdge, 2)*sqr(2.0*freq-ones(freq.size())*(m_emax + m_emin)));
}

Vector KPM::sumSeries(const Vector& freq, const Vector& gP, int chebKind)
{
	Vector sumKPM = zeros(freq.size());
	Vector e = sign(freq).cwiseProduct(sqr(freq));
	ETilde(e);
	Vector	arccosArgument	= arccos(e);
	Vector 	prefactor = ones(freq.size());
	//Vector 	prefactor		= 4*abs(freq)*abs((2.0-m_nuEdge)/c_PI/(m_emax-m_emin));
	if(chebKind == 2)
	{
		prefactor  = 4*abs(freq)*abs((2.0-m_nuEdge)/c_PI/(m_emax-m_emin));
//		prefactor  = 4*sqrt(sqr(freq)+pow(c_PI/m_K/2, 2)*m_emax*ones(freq.size())) * abs((2.0-m_nuEdge)/c_PI/(m_emax-m_emin));

	}
	else
	{
		prefactor  =  2*abs(freq)*abs((2.0-m_nuEdge)/c_PI/(m_emax-m_emin));
		prefactor = prefactor.cwiseProduct( (sqrt(ones(e.size()) - sqr(e))).cwiseInverse() );
	}
	int cof = 1;

	for ( int k =0; k < m_K; ++k)
	{
		if(chebKind == 2)
			sumKPM			+= prefactor.cwiseProduct(( m_jk[k]*gP[k]/m_R)  * sin((k + 1.0) * arccosArgument));
		else
			sumKPM			+= cof*prefactor.cwiseProduct(( m_jk[k]*gP[k]/m_R)  * cos((k) * arccosArgument));

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


