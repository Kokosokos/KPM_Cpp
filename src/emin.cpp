//============================================================================
// Name        : KPM.cpp
// Author      : IVAN
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "KPM.h"
#include <iostream>
#include <fstream>
#include "FileManager.h"

//!!!! Implement ZERO FREQ SHEAR MODULUS output!!!
//!
//!!!! Separate Kernel into interface + jackson, lorentzz....implementations.
//!
using namespace std;


#include <Eigen/Core>
#include <Eigen/SparseCore>


//Parse input arguments
#include <boost/program_options.hpp>
using namespace boost::program_options;

#include <random>
#include <map>
#include <cmath>
#include <iomanip>
#include "core.h"
#include <Eigen/Core>
#include <Eigen/SparseCore>

#include <Spectra/GenEigsSolver.h>
#include <Spectra/MatOp/SparseGenMatProd.h>
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <Spectra/SymEigsSolver.h>
using namespace Spectra;

//SMALLEST_MAGN
bool findLowestE(const sMatrix& hessian, Vector &e, sMatrix& v, int n)
{
	Eigen::VectorXcd evalues;
	SparseGenMatProd<double,  c_myStorageOrder, indexType> op(hessian);
	GenEigsSolver< double, SMALLEST_MAGN, SparseGenMatProd<double, c_myStorageOrder, indexType> > eigs(&op, n, n*5+1);
	// Initialize and compute
	eigs.init();
	eigs.compute(5000, 0.001, SMALLEST_MAGN);
	// Retrieve results
	sMatrix eigenvectors;
	if(eigs.info() == SUCCESSFUL)
	{
		evalues = eigs.eigenvalues();
		Eigen::MatrixXd v1 = eigs.eigenvectors(10).real();
	}
	else
	{
		std::cout << "\nWARNING: Can't calculate Emin: ";
		if( eigs.info() == NOT_CONVERGING)
			std::cout<<"NOT_CONVERGING\n";
		if( eigs.info() == NUMERICAL_ISSUE)
			std::cout<<"NUMERICAL_ISSUE\n";
		return false;
	}
	//	std::cout << "\nEigenvalues found:\n" << evalues << std::endl;
	e = evalues.real();//[0].real();
	return true;
}


int main1(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	Vector emin;
	string affile;
	string resFile;


	vector<string> csrFiles;
	FileManager fmanager;

	Vector af;
	int n=3;
	//Reading arguments

	//------------------------------------------------------------------------------------
	options_description all{"Options"};
	options_description necessary{"Necessary"};

	try
	{

		//		namespace po = boost::program_options;
		necessary.add_options()
	    							  ("help,h", "Help screen")
									  ("csr", value<vector<string>>(&csrFiles)->multitoken()->required(), "Input CSR fromatted matrix. data, indices and indptr filenames.")
									  ("af", value<string>(), "affine force filename")
									  ("n", value<int>(), "number of modes to save");
		all.add(necessary);
		variables_map vm;

		store(parse_command_line(argc, argv, all), vm);
		notify(vm);

		if (vm.count("help") || argc == 1)
		{
			argc = 1;
			std::cout << all << '\n';
			return 0;
		}


		if( csrFiles.size() == 3 )
		{
			cout<<"CSR files: "<<csrFiles[0]<< " "<<  csrFiles[1]<<" "<<csrFiles[2]<<endl;
		}
		else
		{
			cout << "Error: Please provide 3 files when using --csr: data, indices and indptr."<<endl;
			return 0;
		}

		if (vm.count("af") )
		{
			affile = vm["af"].as<string>();
		}
		else
		{
			cout << "Error: Please provide AF file name."<<endl;
			return 0;
		}

		if (vm.count("n") )
		{
			n = vm["n"].as<int>();
		}
		else
		{
			cout << "Error: Please provide N, number of lowest eigvalues."<<endl;
			return 0;
		}
		cout<<"Parsing input args ended..\n";

	}
	catch (const error &ex)
	{
		std::cerr << ex.what() << '\n';
		std::cout << all << '\n';
		return 0;
	}
	//------------------------------------------------------------------------------------


	//KPM START
	//------------------------------------------------------------------------------------
	processStatus("KPM started");
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	clock_t t;
	clock_t tstart;
	tstart = clock();
	sMatrix hessian;
	processStatus(string("main: Reading matrix....mem: ") + mem());
	fmanager.readCSR(csrFiles[0], csrFiles[1], csrFiles[2], hessian);
	processStatus(string("main: Reading matrix... Finished mem: ")+ mem() );
	//------------------------------------------------------------------------------------



	tstart = clock();
	sMatrix v;

	Vector e=zeros(10);
	fmanager.read(affile, af);
	findLowestE( hessian, e,v,n);
	std::cout<<e<<std::endl;
	//	fmanager.write("Gpp.dat",logfreq, Gpp);

	t = clock() - tstart;
	processStatus(string("It took me ")+ to_string(((float)t)/CLOCKS_PER_SEC) +"seconds.");

	MPI_Finalize();
	return 0;
}
