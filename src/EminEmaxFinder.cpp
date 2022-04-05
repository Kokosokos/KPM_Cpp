#include "EminEmaxFinder.h"
#include "FileManager.h"


#include <Spectra/GenEigsSolver.h>
#include <Spectra/MatOp/SparseGenMatProd.h>
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <Spectra/SymEigsSolver.h>
using namespace Spectra;

vector<double> EminEmaxFinder::findEminEmax( const vector<string>& csrFiles)
{
	FileManager fmanager;
	auto hessian = std::move(fmanager.readCSR(csrFiles[0], csrFiles[1], csrFiles[2]));
	if (!hessian)
	{
		processStatus("ERROR!!! while reading Hessian");
		return {10,-10}; //error indicator, coz emin must be <= emax
	}

	float emin = findEmin(*hessian);
	float emax = findEmax(*hessian);

	return {emin, emax};
};

double EminEmaxFinder::findEmin(const sMatrix& hessian)
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder, indexType> op(hessian);
	GenEigsSolver< SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(op, 3, 20);
	// Initialize and compute
	eigs.init();
	eigs.compute(SortRule::SmallestReal, 5000, 0.001);
	// Retrieve results
	if(eigs.info() == CompInfo::Successful)
		evalues = eigs.eigenvalues();
	else
	{
		std::cout << "\nWARNING: Can't calculate Emin: ";
		if( eigs.info() == CompInfo::NotConverging)
			std::cout<<"NOT_CONVERGING\n";
		if( eigs.info() == CompInfo::NumericalIssue)
			std::cout<<"NUMERICAL_ISSUE\n";
		return false;
	}
	//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	return  evalues[0].real();
}

double EminEmaxFinder::findEmax(const sMatrix& hessian)
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder,indexType> op(hessian);

	// Construct eigen solver object, requesting the largest three eigenvalues
	GenEigsSolver< SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(op, 3, 7);
	// Initialize and compute
	eigs.init();
	eigs.compute(SortRule::LargestMagn);
	// Retrieve results
	if(eigs.info() == CompInfo::Successful)
		evalues = eigs.eigenvalues();
	else
	{
		std::cout << "WARNING: Can't calculate Emax:\n";
		return false;
		//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	}
	return evalues[0].real();
}
