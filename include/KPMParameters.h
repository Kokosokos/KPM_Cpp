/*
 * KPMParameters.h
 *
 *  Created on: Apr 2, 2022
 *      Author: ivan
 */

#ifndef INCLUDE_KPMPARAMETERS_H_
#define INCLUDE_KPMPARAMETERS_H_

#include "core.h"

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
	float GA; 		//affine shear modulus
	float density;
	float nu; 		//~friction coeff
	float wmin;     //atom, CG: 0.1
	float wmax;  	//atom, CG: 1000
	unsigned int wcount;//atom, CG: 200

//GDOS params
	float wcut;
	int nFreq;
//	KPMGParams():GA{0.0}, density{1.0}, nu{1.0}, wmin{1.0}, wmax{100000}, nw{400},c_wcut{0.001},nFreq(4000){};
	KPMGParams(float GAT=0.0, float density=1.0, float nuT=1.0,float wminT=1.0, float wmaxT=100000, unsigned int nPoints=400 ):
				GA{GAT}, density{density}, nu{nuT}, wmin{wminT}, wmax{wmaxT}, wcount{nPoints},wcut{0.001},nFreq(4000){};

	using Pointer = std::unique_ptr<KPMGParams>;
};

struct KPMParams
{
	KPMMode mode;
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
	float		epsilon;
	KPMKernels	kernel;
	int			lkernel;
	float		emin;
	float		emax;
	/**
	 * @brief Jackson kernel
	 */
	Vector		m_jk;

	//If mode == KPMMode::GDOS
	float density;
	std::string lammps_data_file;
	std::string af_file;
	Vector MinvSqrt;
	Vector af;
//	VectorPointer MinvSqrt;
//	VectorPointer af;
public:
	KPMParams():epsilon(0.05),kernel(KPMKernels::Jackson),lkernel(0),emin(0.0f),emax(0.0f){};
	bool readFromFile(std::string filename);
	bool readAF();
	bool readM();
	bool writeToFile(std::string filename);
	void setAF(const Vector& af);
	void setMassVectorInvSqrt(const Vector& mInvSqrt);
	void setMassVectorInvSqrt(float m, unsigned int DOF);

	void setK(unsigned int K);
	void setR(unsigned int RR){R = RR;};
	void setEpsilon(float epsilonT){epsilon = epsilonT;};
	void setEminEmax(float eminT, float emaxT){emin = eminT;emax = emaxT;};
	void setKernel(KPMKernels kernelT){kernel = kernelT;};
	void setLKernel(int lT){lkernel = lT;};

	void jacksonKernel(int K);
	void lorentzKernel(int K, int parameter=4);

	unsigned int getK() const {return K;};
	unsigned int getR() const {return  R;};
	float getEpsilon()  const {return epsilon;};
	float getEmin() const {return emin;};
	float getEmax() const {return emax;};
	float getNu() const {return epsilon;};
	KPMKernels getKernel() const {return kernel;};
	int getLKernel() const {return lkernel;};

	using Pointer = std::unique_ptr<KPMParams>;
};


#endif /* INCLUDE_KPMPARAMETERS_H_ */
