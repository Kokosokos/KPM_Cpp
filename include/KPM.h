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


using namespace std;

class KPM {
public:
	//Read-write methods. Must be separated.
	//-----------------------------------------
	/**
	 * @brief Reads the CSR-matrix from 3 files: m_fndata, m_fnindptr, m_fnindptr
	 */
	void readCSR();
	void write(string filename, Vector v1, Vector v2);
	void write(string filename, Vector v1);
	void  readAF(string filename);
	void readLAMMPSData(string filename); //reads m_M (particle masses) from lammps data file

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
	 * @brief Sets maximum polynomial degree. Invokes @jacksonKernel(K)@ to recalculate jackson kernel.
	 */
	void setK(unsigned int K);
	void setR(unsigned int R);

	KPM();
	KPM(unsigned int K, unsigned int R, float nuEdge = 0.05);
	virtual ~KPM();

	double aScaling();
	double bScaling();
	void ETilde(Vector& e);
	void HTilde();

	void jacksonKernel(int K);

	Vector getCoeffDOS();
	Vector getCoeffGammaDOS();
	Vector sumSeries(const Vector& freq, const Vector& gP);



	//private:
	//INPUT filenames
	//-----------------------------------------

	/**
	 * @brief Filename of the data of the CSR-matrix.
	 */
	string m_fndata;
	/**
	 * @brief Filename of the indptr of the CSR-matrix.
	 * "indptr" shows the cumulative number of non zero elements in each row.,
	 */
	string m_fnindptr;
	/**
	 * @brief Filename of the indices of the CSR-matrix.
	 * "indices" shows the column index of all non zero elements.
	 */
	string m_fnindices;

	/**
	 * @brief Filename of the affine force field vector. (Needed for GammaDOS and G'(G'') calculations. Not needed for VDOS only.)
	 */
	string m_faf;
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
	int m_emax;


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
