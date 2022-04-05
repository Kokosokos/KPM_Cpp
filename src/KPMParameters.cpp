/*
 * KPMParameters.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: ivan
 */

#include "KPMParameters.h"

void KPMParams::setMassVectorInvSqrt(float m, unsigned int DOF)
{
	MinvSqrt = 1.0 / sqrt(m) * ones(DOF);
//	m_MinvSqrt = Vector::Map(massesFull.data(), massesFull.size());
}
//-------------------------------------------------------------------------------

void KPMParams::setMassVectorInvSqrt( const Vector& mInvSqrt)
{
	MinvSqrt = mInvSqrt;

}
//-------------------------------------------------------------------------------

void KPMParams::setAF(const Vector& iaf)
{
	af = MinvSqrt.cwiseProduct( iaf );
}

void KPMParams::setK(unsigned int KK)
{
	K = KK;
	//Jackson kernel
	if(kernel == KPMKernels::Jackson)
		jacksonKernel(K);
	if(kernel == KPMKernels::Lorentz)
		lorentzKernel(K, lkernel);
}

void KPMParams::jacksonKernel(int K)
{
	Vector n = arange(K);
	m_jk = ((K+1)*ones(n.size())-n);

	m_jk = m_jk.cwiseProduct( cos((c_PI/(K+1))*n));
	m_jk += sin(c_PI*n/(K+1))/tan(c_PI/(K+1)) ;
	m_jk *= (1.0/(K+1));
}
void KPMParams::lorentzKernel(int K, int parameter )
{
	Vector n = arange(K);
	m_jk = sinh(parameter*(ones(n.size())-n/K))/sinh(parameter);
}
