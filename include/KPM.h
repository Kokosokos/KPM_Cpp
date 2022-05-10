#ifndef KPM_H_
#define KPM_H_
#include "core.h"
#include <iostream>
#include <stdio.h>

#include "FileManager.h"
#include "KPMParameters.h"

using namespace std;

class KPM
{

public:
	KPM(sMatrixPointer hessian, const KPMParams& params,  const vector<int>&sizes, const vector<int>&displacements, MPI_Comm inworld=MPI_COMM_WORLD);
	KPM(const KPMParams& params, const Vector& gp);
	~KPM() = default;

	virtual void calculateCoefficients(int chebKind = 2); // 1 or 2
	const Vector& getCoefficients() const;
	Vector sumSeries(const Vector& freq, int chebKind = 2);

	using Pointer = std::unique_ptr<KPM>;

protected:
	void HTilde();
	double aScaling();
	double bScaling();
	void ETilde(Vector& e);

	/**
	 * @brief Total degrees of freedom/matrix size
	 */
	unsigned int m_DOF;
	/**
	 * @brief Hessian matrix.
	 */
	sMatrixPointer  m_hessian;
	Vector			m_gp;
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
class KPMDOS: public KPM
{
public:
//	using KPM::KPM;
	KPMDOS(sMatrixPointer hessian, const KPMParams& params, const vector<int>&sizes, const vector<int>&displacements,MPI_Comm inworld);
	virtual void calculateCoefficients(int chebKind = 2) override;

	using Pointer = std::unique_ptr<KPMDOS>;
};

class KPMGammaDOS: public KPM
{
public:
	KPMGammaDOS(sMatrixPointer hessian, const KPMParams& params, const vector<int>&sizes, const vector<int>&displacements,MPI_Comm inworld);
	virtual void calculateCoefficients(int chebKind = 2) override;
//	using KPM::KPM;
	using Pointer = std::unique_ptr<KPMGammaDOS>;
private:
};

class ShearModulus
{
public:
	ShearModulus() = default;
	~ShearModulus() = default;

	Vector getStorage(KPMGParams params,  const Vector& gdos_freq, const Vector& gdos, const Vector& freq);
	Vector getLoss(KPMGParams params, const Vector& gdos_freq, const Vector& gdos, const Vector& freq);
};


#endif /* KPM_H_ */
