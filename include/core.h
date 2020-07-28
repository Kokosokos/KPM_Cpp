/*
 * matrixVector.h
 *
 *  Created on: 6 Nov 2018
 *      Author: ikriuchevs
 */
#define EIGEN

#ifndef __CORE_H_
#define __CORE_H_

//#define WITHOPENCV
#include <iostream>

const double c_PI=3.14159;

#ifndef EIGEN
#include <blaze/Blaze.h>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/DynamicMatrix.h>

//// Definition of a 4x6 single precision row-major matrix
typedef blaze::CompressedMatrix<float,blaze::rowMajor> sMatrix;
typedef blaze::DynamicVector<float,blaze::rowMajor> Vector;

#else
#include <Eigen/Sparse>

const   Eigen::StorageOptions c_myStorageOrder =  Eigen::RowMajor;

typedef Eigen::SparseMatrix<double, c_myStorageOrder> sMatrix;
typedef Eigen::VectorXd Vector;


//Numpy-like functions
inline Vector ones(int size)
{
	return Vector::Ones(size);
}

inline Vector zeros(int size)
{
	return Vector::Zero(size);
}

inline  Vector arange(int N)
{
	return Vector::LinSpaced(N,0,N-1);
}

inline  Vector arange(int N, float min, float max)
{
	return Vector::LinSpaced(N,0,max);
}

inline  Vector sin(Vector v)
{
	return Eigen::sin(v.array());
}

inline  Vector cos(Vector v)
{
	return Eigen::cos(v.array());
}

inline Vector arccos(Vector v)
{
	return Eigen::acos(v.array());
}

inline Vector sign(Vector v)
{
	return v.array().sign();
}

inline Vector sqr(Vector v)
{
	return v.array().square();
}

inline Vector abs(Vector v)
{
	return v.array().abs();
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#include <Eigen/Dense>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <time.h>       /* time for the seed*/
/*
  We need a functor that can pretend it's const,
  but to be a good random number generator
  it needs mutable state.
 */
namespace Eigen {
namespace internal {
template<typename Scalar>
struct scalar_normal_dist_op
{
	static boost::mt19937 rng;    // The uniform pseudo-random algorithm
	mutable boost::normal_distribution<Scalar> norm;  // The gaussian combinator

	EIGEN_EMPTY_STRUCT_CTOR(scalar_normal_dist_op)

	template<typename Index>
	inline const Scalar operator() (Index, Index = 0) const { return norm(rng); }
};

template<typename Scalar> boost::mt19937 scalar_normal_dist_op<Scalar>::rng;

template<typename Scalar>
struct functor_traits<scalar_normal_dist_op<Scalar> >
{ enum { Cost = 50 * NumTraits<Scalar>::MulCost, PacketAccess = false, IsRepeatable = false }; };
} // end namespace internal
} // end namespace Eigen

inline Vector normal( unsigned int nn, int seed)
{
	int size = 1; // Dimensionality (rows)
//	int nn=50;     // How many samples (columns) to draw
	Eigen::internal::scalar_normal_dist_op<double> randN; // Gaussian functor
	Eigen::internal::scalar_normal_dist_op<double>::rng.seed(seed); // Seed the rng
	Eigen::VectorXd mean(size);
	Eigen::MatrixXd covar(size,size);
	mean[0]=0;
	covar(0,0)=1;
	Eigen::MatrixXd normTransform(size,size);

	Eigen::LLT<Eigen::MatrixXd> cholSolver(covar);

	// We can only use the cholesky decomposition if
	// the covariance matrix is symmetric, pos-definite.
	// But a covariance matrix might be pos-semi-definite.
	// In that case, we'll go to an EigenSolver
	if (cholSolver.info()==Eigen::Success) {
		// Use cholesky solver
		normTransform = cholSolver.matrixL();
	} else {
		// Use eigen solver
		Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigenSolver(covar);
		normTransform = eigenSolver.eigenvectors()
	                		   * eigenSolver.eigenvalues().cwiseSqrt().asDiagonal();
	}

	Eigen::MatrixXd samples = (normTransform
			* Eigen::MatrixXd::NullaryExpr(size,nn,randN)).colwise()
	                        		   + mean;

	return samples.row(0);
}

inline Vector normal( unsigned int nn)
{

	return normal(nn, int(time(NULL)));
}


inline void processRunningStatus(float progress)
{
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

inline void processEnded()
{
	 std::cout<<std::endl;
	 std::cout.flush();
}
#endif

#include "mpi.h"


#endif /* __CORE_H_ */
