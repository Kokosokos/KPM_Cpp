/*
 * KPM.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ivan
 */

#include "KPM.h"
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <Spectra/GenEigsSolver.h>
#include <Spectra/MatOp/SparseGenMatProd.h>
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <Spectra/SymEigsSolver.h>
using namespace Spectra;

KPM::KPM():m_nuEdge(0.05), m_R(100)  {
	setK(100);
	m_fndata	= "test/H.data.dat";
	m_fnindptr	= "test/H.indptr.dat";
	m_fnindices	= "test/H.indices.dat";

	readCSR();

}

KPM::KPM(unsigned int K, unsigned int R, float nuEdge):m_nuEdge(nuEdge),  m_R(R)
{
	m_fndata	= "test/H.data.dat";
	m_fnindptr	= "test/H.indptr.dat";
	m_fnindices	= "test/H.indices.dat";
	setK(K);
	readCSR();

}


KPM::~KPM() {
	// TODO Auto-generated destructor stub
}
void KPM::write(string filename, Vector v1, Vector v2)
{
	FILE *stream;
	stream = fopen(filename.c_str(), "w");
	for(int i = 0; i< v1.size(); ++i )
	{
		fprintf(stream, "%f %f\n", v1[i], v2[i]);
	}
	fclose(stream);
}

void KPM::write(string filename, Vector v1)
{
	FILE *stream;
	stream = fopen(filename.c_str(), "w");
	for(int i = 0; i< v1.size(); ++i )
	{
		fprintf(stream, "%f\n", v1[i]);
	}
	fclose(stream);
}

void  KPM::readAF(string filename)
{
	FILE *stream;
	stream = fopen(filename.c_str(), "r");
	for(int i = 0; i< v1.size(); ++i )
	{
		fprintf(stream, "%f\n", v1[i]);
	}
	fclose(stream);
}
void KPM::readCSR()
{

	//Read indptr from CSR matrix (== cumulative number of nonzero elements in a row)
	//	vector<int> T(100000, 22);
	vector<int> indptr;
	FILE *stream;
	stream = fopen(m_fnindptr.c_str(), "r");
	if (stream==NULL) perror ("Error opening file for indptr");

	int val;
	while(fscanf(stream, "%d", &val) != EOF)
	{
		indptr.push_back(val);
	}
	fclose(stream);
	unsigned int N=indptr.size()-1;
	cout<<"N:"<<N<<endl;

	m_DOF = N;

	//Read data and column indices
	int nNon0 = *(indptr.end()-1); //number of non zero elements

	FILE *stream3;
	stream3 = fopen(m_fndata.c_str(), "r");
	float dataval=0.0f;
	vector <float> data;
	for (int i =0; i < nNon0;++i)
	{
		if(fscanf(stream3, "%f", &dataval) == EOF)  perror ("Error: datafile has too few elements");
		data.push_back(dataval);
	}
	fclose(stream3);

	FILE *stream2;
	stream2 = fopen(m_fnindices.c_str(), "r");
	int indval=0;
	vector <int> indices;
	for (int i =0; i < nNon0;++i)
	{
		if(fscanf(stream, "%d", &indval) == EOF)  perror ("Error: datafile has too few elements");
		indices.push_back(indval);
	}
	fclose(stream2);
	int rowLen = 0;
	m_nnonzero = indptr[N];

	//Create sparse matrix
	m_hessian = sMatrix(N,N);
	// Reserving enough space for non-zero elements


#ifndef EIGEN
	m_hessian.reserve( m_nnonzero );
	for (unsigned int i =0; i < N ;++i)
	{
		rowLen = indptr[i+1] - indptr[i];


		for (int j =0;j <rowLen;++j)
		{
			int k = indptr[i] + j;
			m_hessian.append( i, indices[k]-1, data[k] );
		}

		m_hessian.finalize( i );
	}
	cout<<"Hessian's first element: "<<m_hessian(1,1)<<endl;
#else
	vector<int> sizes(N);
	for (unsigned int i =0; i < N ;++i)
	{
		sizes[i]=indptr[i+1] - indptr[i];
	}
	m_hessian.reserve( sizes );
	for (unsigned int i =0; i < N ;++i)
	{
		rowLen = indptr[i+1] - indptr[i];


		for (int j =0;j <rowLen;++j)
		{
			int k = indptr[i] + j;
			m_hessian.insert( i, indices[k]-1) =  data[k] ;
		}
	}
	//	m_hessian.makeCompressed();
	//get 1 element
//	cout<<m_hessian.coeff(1,1);
#endif

}

void KPM::findEmin()
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder> op(m_hessian);
	GenEigsSolver< double, SMALLEST_REAL, SparseGenMatProd<double, c_myStorageOrder> > eigs(&op, 3, 7);
	// Initialize and compute
	eigs.init();
	int nconv = eigs.compute();
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
	SparseGenMatProd<double,  c_myStorageOrder> op(m_hessian);

	// Construct eigen solver object, requesting the largest three eigenvalues
	GenEigsSolver< double, LARGEST_MAGN, SparseGenMatProd<double, c_myStorageOrder> > eigs(&op, 3, 7);
	// Initialize and compute
	eigs.init();
	int nconv = eigs.compute();
	// Retrieve results
	if(eigs.info() == SUCCESSFUL)
		evalues = eigs.eigenvalues();
	else
		std::cout << "WARNING: Can't calculate Emax:\n";

	//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	m_emax = evalues[0].real();
}

void KPM::setK(unsigned int K)
{
	m_K = K;
	jacksonKernel(K);
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
	const double a(aScaling());
	const double  b(bScaling());

	e = (e-b*ones(e.size()))/a;

}
void KPM::HTilde()
{
	double  a = aScaling();
	double  b = bScaling();

	m_hessian.diagonal() -= b*ones(m_hessian.rows());
	//m_hessian = m_hessian - b*Eigen::MatrixXd::Identity(m_hessian.rows(), m_hessian.cols());
	m_hessian /= a;
}

void KPM::jacksonKernel(int K)
{
	Vector n = arange(K);
	m_jk = ((K+1)*ones(n.size())-n);

	m_jk = m_jk.cwiseProduct( cos((c_PI/(K+1))*n));
	m_jk += sin(c_PI*n/(K+1))/tan(c_PI/(K+1)) ;
	m_jk *= (1.0/(K+1));
}
//Vector KPM::DOS()
//{
//	Vector gP = zeros(m_K); // gauss projection
//	for (int r = 0; r < m_R; ++r)
//	{
//		if (r % 10 == 0)
//			cout<<float(r)/m_R*100<<"%"<<endl;
//		//k = 0
//		Vector v_r = normal(m_DOF);
//		v_r=v_r/v_r.norm();
//		Vector polyChebCurr = v_r;
//		Vector polyChebPrevPrev = v_r;
//		Vector polyChebPrev = v_r;
//
//		gP[0] += v_r.transpose() * polyChebCurr;
//
//		//k = 1
//		polyChebCurr = 2 * m_hessian * polyChebPrev;
//		polyChebPrevPrev = polyChebPrev;
//		polyChebPrev = polyChebCurr;
//
//		gP[1] += v_r.transpose() * polyChebCurr;
//
//		for (int k = 2; k < m_K; ++k)
//		{
//
//			polyChebCurr = 2 * m_hessian * polyChebPrev - polyChebPrevPrev;
//			polyChebPrevPrev = polyChebPrev;
//			polyChebPrev = polyChebCurr;
//
//			gP[k] += v_r.transpose() * polyChebCurr;
//		}
//	}
//	return gP;
//}

Vector KPM::getCoeffDOS()
{
	Vector loc_gP = zeros(m_K); // gauss projection
	Vector glob_gP = zeros(m_K); // gauss projection
	int rank = MPI::COMM_WORLD.Get_rank();
	int size = MPI::COMM_WORLD.Get_size();
	for (int r = rank; r < m_R; r+=size)
	{
		if (r % 10 == 0)
			cout<<float(r)/m_R*100<<"%"<<endl;
		//k = 0
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
			polyChebPrevPrev = polyChebPrev;
			polyChebPrev = polyChebCurr;

			loc_gP[k] += v_r.transpose() * polyChebCurr;
		}
	}
	//MPI::COMM_WORLD.Reduce(loc_gP.array(), glob_gP.array(), m_K, MPI::DOUBLE, MPI::SUM, 0);
	MPI::COMM_WORLD.Reduce(loc_gP.data(), glob_gP.data(), m_K, MPI::DOUBLE, MPI::SUM, 0);
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

		sumKPM			+= prefactor.cwiseProduct(( m_jk[k]*gP[k]/m_R)  * sin((k + 1) * arccosArgument));

	}
	return sumKPM;
}
