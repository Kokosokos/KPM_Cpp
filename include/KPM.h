/*
 * KPM.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ivan
 */

#ifndef KPM_H_
#define KPM_H_
#include <iostream>
#include <stdio.h>
#include "core.h"
#include "FileManager.h"

using namespace std;

class KPM {
public:
	//Read-write methods. Must be separated.
	//-----------------------------------------
	/**
	 * @brief Reads the CSR-matrix from 3 files: m_fndata, m_fnindptr, m_fnindptr
	 */
	void setMassVectorInvSqrt( const Vector& mInvSqrt);
	void constMass(float m);
	//-----------------------------------------


	/**
	 * @brief Finds minimum eigenvalue.
	 */
	void findEmin();
	/**
	 * @brief Finds maximum eigenvalue.
	 */
	void findEmax();
	/**
	 * @brief Set minimum eigenvalue.
	 */
	void setEmin( const float& emin);
	/**
	 * @brief Set maximum eigenvalue.
	 */
	void setEmax( const float& emax);


	float getEmin() const;
	float getEmax() const;

	/**
	 * @brief Sets maximum polynomial degree. Invokes @jacksonKernel(K)@ to recalculate jackson kernel.
	 */
	void setK(unsigned int K);
	void setR(unsigned int R);
	int getK();
	int getR();

	void setAF(const Vector& af);

//	KPM(); add hessian set flag??
	KPM(const sMatrix& hessian, unsigned int K, unsigned int R, float nuEdge = 0.05);
	virtual ~KPM();



	Vector getCoeffDOS();
	Vector getCoeffGammaDOS();
	Vector sumSeries(const Vector& freq, const Vector& gP);

	Vector getModulus(const float& GA,  const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq );
	Vector getModulusImag(const float& GA, const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq );

	void HTilde();

	private:

	double aScaling();
	double bScaling();
	void ETilde(Vector& e);


	void jacksonKernel(int K);
	//INPUT filenames
	//-----------------------------------------

	//-----------------------------------------

	/**
	 * @brief Total number of non zero elements in the matrix
	 */
	unsigned int m_nnonzero;

	/**
	 * @brief Total degrees of freedom/matrix size
	 */
	unsigned int m_DOF;
	/**
	 * @brief Hessian matrix.
	 */
	sMatrix  m_hessian;

	/**
	 * @brief Affine force field vector.
	 */
	Vector m_af;

	/**
	 * @brief Vector of particle masses (x dim)
	 */
	Vector m_M;

	/**
	 * @brief Vector of particle masses (inverse squared)
	 */
	Vector m_MinvSqrt;

	/**
	 * @brief MAximum eigenvalue
	 */
	double m_emax;


	/**
	 * @brief Minimum eigenvalue
	 */
	double m_emin;
	/**
	 * @brief MAximum degree of polynomial
	 */
	int m_K;

	/**
	 * @brief Number of random vectors
	 */
	double m_R;



	/**
	 * @brief Jackson kernel
	 */
	Vector m_jk;


	/**
	 * @brief "Safety" measure for rescaling the Hesiian into [-1+m_nuEdge/2, 1-m_nuEdge] (since there is a finite precision in Emin Emax definition).
	 */
	float m_nuEdge;

};

#endif /* KPM_H_ */
