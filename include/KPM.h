#ifndef KPM_H_
#define KPM_H_
#include "core.h"
#include <iostream>
#include <stdio.h>

#include "FileManager.h"
#include "KPMParameters.h"

using namespace std;

class KPM {
public:
	KPM(sMatrixPointer hessian, const KPMParams& params,  const vector<int>&sizes, const vector<int>&displacements, MPI_Comm inworld=MPI_COMM_WORLD);
	~KPM() = default;

	void setMassVectorInvSqrt( const Vector& mInvSqrt);
	void constMass(float m);
	void setEminEmax( const float& emin, const float& emax);
	void setAF(const Vector& af);

	Vector getCoeffDOS(int chebKind = 2); // 1 or 2
	Vector getCoeffGammaDOS();
	Vector getCoeffGammaDOS(vector<int> sizes, vector<int> displacements);
	Vector sumSeries(const Vector& freq, const Vector& gP, int chebKind = 2);

	//Different Class!!
	Vector getModulus(const float& GA,  const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq, float nu=1.0);
	Vector getModulusImag(const float& GA, const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq, float nu=1.0);


	private:
	void HTilde();
	double aScaling();
	double bScaling();
	void ETilde(Vector& e);

	public:
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
	sMatrixPointer  m_hessian;

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
	 * @brief Parameters of the KPM
	 */
	KPMParams m_params;

	MPI_Comm m_world;
	vector<int>m_sizes;
	vector<int>m_displacements;
	int m_mpi_rank;
	int m_mpi_size;

};

#endif /* KPM_H_ */
