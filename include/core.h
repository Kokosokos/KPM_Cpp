/*
 * matrixVector.h
 *
 *  Created on: 6 Nov 2018
 *      Author: ikriuchevs
 */
#define EIGEN
#define EIGEN_DEFAULT_DENSE_INDEX_TYPE long long int
#ifndef __CORE_H_
#define __CORE_H_

//#define WITHOPENCV
#include <iostream>

const double c_PI=3.14159;


#include <Eigen/Sparse>

const   Eigen::StorageOptions c_myStorageOrder =  Eigen::RowMajor;
typedef long int indexType;
//typedef int indexType;
typedef Eigen::SparseMatrix<double, c_myStorageOrder> sMatrix2;
typedef Eigen::SparseMatrix<double, c_myStorageOrder, indexType> sMatrix;
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
	return Vector::LinSpaced(N,min,max);
}

inline  Vector logspace(int N, float min, float max)
{
	float minPow = log10(min);
	float maxPow = log10(max);
	return Eigen::pow(10,Vector::LinSpaced(N,minPow,maxPow).array());
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

inline float trapz(Vector y, Vector x)
{
	int imax = x.size();
	double integral = 0.0;

	for (int i = 1; i < imax; ++i)
	{
		integral += (x[i]-x[i-1]) * (y[i] + y[i-1]) / 2.0;
	}
	return integral;
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

#include <random>
#include <algorithm>
auto normalrnd = [](float mean, float sigma)
{
    auto randomFunc = [distribution_ = std::normal_distribution<>(mean, sigma),
                       random_engine_ = std::mt19937{ std::random_device{}() }]() mutable
    {
        return distribution_(random_engine_);
    };
    return randomFunc;
};

inline Vector normal( unsigned int nn)
{

	std::vector<double> numbers;
//	Vector res(nn);
	std::generate_n(std::back_inserter(numbers), nn, normalrnd(0.0, 1.0));
	return  Vector::Map(numbers.data(), numbers.size());
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

#include "mpi.h"


#endif /* __CORE_H_ */
