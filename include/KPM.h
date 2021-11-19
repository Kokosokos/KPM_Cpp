/*
 * KPM.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ivan
 */

#ifndef KPM_H_
#define KPM_H_
#include "core.h"
#include <iostream>
#include <stdio.h>

#include "FileManager.h"

using namespace std;
enum class KPMCalculation
{
	Full = 0, // Calculate coefficients and the kpm sum
	Sum  = 1 // Only sum, assuming u calculated the coefficients before
};
enum class KPMMode
{
	DOS, //Calculate vibrational density of states
	GDOS //Calculate gamma correlator + shear modulus vs frequency
};
enum class KPMKernels
{
	Jackson, //Default
	Lorentz
};

struct KPMGParams
{
private:
	float GA; //affine shear modulus
	float Volume;
	float nu; //~friction coeff
	float wmin;     //atom, CG: 0.1
	float wmax;  //atom, CG: 1000
	unsigned int nw;//atom, CG: 200
public:
	KPMGParams();
	KPMGParams(float GAT, float V, float nuT,float wminT, float wmaxT, unsigned int nPoints ):
				GA(GAT), Volume(V), nu(nuT), wmin(wminT), wmax(wmaxT), nw(nPoints){};
	void setGA(float GAT)      {GA = GAT;};
	void setVolume(float volT)      {Volume = volT;};
	void setFriction(float nuT){nu = nuT;};
	void setFreqRange(float wminT, float wmaxT, unsigned int nPoints)
	{
		wmin = wminT;
		wmax = wmaxT;
		nw = nPoints;
	};
	float getGA() const { return GA;};
	float getVolume() const {return Volume;};
	float getFriction() const { return nu;};
	float getWmin() const { return wmin;};
	float getWmax() const { return wmax;};
	unsigned int getNPoints() const {return nw;};
};
struct KPMParams
{
private:
	/**
	 * @brief MAximum degree of polynomial
	 */
	unsigned int K;
	/**
	 * @brief Number of random vectors
	 */
	unsigned int R;
	/**
	 * @brief "Safety" measure for rescaling the Hesiian into [-1+m_nuEdge/2, 1-m_nuEdge] (since there is a finite precision in Emin Emax definition).
	 */
	float epsilon;
	//True = find eminemax, False = dont need to find, already set
	bool find_eminmax;
	float emin;
	float emax;
	KPMKernels kernel;
	int lkernel;
public:
	KPMParams():epsilon(0.05),kernel(KPMKernels::Jackson),lkernel(0),find_eminmax(true),emin(0.0f),emax(0.0f){};
	void setK(unsigned int KK){K = KK;};
	void setR(unsigned int RR){R = RR;};
	void setEpsilon(float epsilonT){epsilon = epsilonT;};
	void setFindEminEmax(bool yesNo){find_eminmax = yesNo;};
	void setEminEmax(float eminT, float emaxT){emin = eminT;emax = emaxT;find_eminmax=false;};
//	void setEmax(float emaxT){emax = emaxT;};
	void setKernel(KPMKernels kernelT){kernel = kernelT;};
	void setLKernel(int lT){lkernel = lT;};


	unsigned int getK() const {return K;};
	unsigned int getR() const {return  R;};
	float getEpsilon()  const {return epsilon;};
	bool getFindEminEmax() const {return find_eminmax;};
	float getEmin() const {return emin;};
	float getEmax() const {return emax;};
	float getNu() const {return epsilon;};
	KPMKernels getKernel() const {return kernel;};
	int getLKernel() const {return lkernel;};
};
class FindEminEmax //~wrapper for specta functions
{
public:
	FindEminEmax(){};
	/**
	 * @brief Finds minimum eigenvalue.
	 */
	double findEmin(const sMatrix& hessian);
	/**
	 * @brief Finds maximum eigenvalue.
	 */
	double findEmax(const sMatrix& hessian);

};

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



	void setEminEmax( const float& emin, const float& emax);

	float getEmin() const;
	float getEmax() const;

	/**
	 * @brief Sets maximum polynomial degree. Invokes @jacksonKernel(K)@ to recalculate jackson kernel.
	 */
	void setK(unsigned int K, KPMKernels kernel = KPMKernels::Jackson, int lkernel = 0);
	void setR(unsigned int R);
	int getK();
	int getR();

	void setAF(const Vector& af);

//	KPM(); add hessian set flag??
//	KPM(sMatrix& hessian, unsigned int K, unsigned int R, float nuEdge = 0.05, MPI_Comm inworld=MPI_COMM_WORLD, string kernel="jk", int lkernel = 0);
	KPM(sMatrix& hessian, const KPMParams& params,  const vector<int>&sizes, const vector<int>&displacements, MPI_Comm inworld=MPI_COMM_WORLD);
	virtual ~KPM();



	Vector getCoeffDOS(int chebKind = 2); // 1 or 2
	//If not privided use simple MPI_gather!!!
	Vector getCoeffGammaDOS();
	Vector getCoeffGammaDOS(vector<int> sizes, vector<int> displacements);
	Vector getKArray(float dfreq);
	Vector getKArray(const Vector& freq);
	Vector getSpreading(Vector freq);
	Vector sumSeries(const Vector& freq, const Vector& gP, int chebKind = 2);

	Vector getModulus(const float& GA,  const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq, float nu=1.0);
	Vector getModulusImag(const float& GA, const float& volume, const Vector& gdos_freq, const Vector& gdos, const Vector& freq, float nu=1.0);

	void HTilde();

//	private:

	double aScaling();
	double bScaling();
	void ETilde(Vector& e);


	void jacksonKernel(int K);
	void lorentzKernel(int K, int parameter=4);
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
	sMatrix&  m_hessian;
//	sMatrix  m_hessian_rank;

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
	/**
	 * @brief Jackson kernel
	 */
	Vector m_jk;


	/**
	 * @brief "Safety" measure for rescaling the Hesiian into [-1+m_nuEdge/2, 1-m_nuEdge] (since there is a finite precision in Emin Emax definition).
	 */
	MPI_Comm m_world;
	vector<int>m_sizes;
	vector<int>m_displacements;
	int m_mpi_rank;
	int m_mpi_size;

};

#endif /* KPM_H_ */
