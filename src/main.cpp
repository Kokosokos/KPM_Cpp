//============================================================================
// Name        : KPM.cpp
// Author      : IVAN
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "KPM.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>

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
//


int parseInput(int argc, char* argv[], KPMParams& params, KPMCalculation& kpmCalc,
				vector<string>& csrFiles, vector<string>& gpFiles );
int main(int argc, char* argv[])
{
#ifdef DETERMINISTIC
	processStatus("DETERMINISTIC run");
#endif
	auto GA = FileManager::readKPMGParameters("kpmG.config").GA;
	auto kpmGParams = FileManager::readKPMGParameters("kpmG.config");
	MPI_Init(&argc, &argv);

	FileManager fmanager;
	vector<string> csrFiles;
	string gpFile;
	string resFile;

	KPMParams kpmParams;
	KPMCalculation kpmCalc;

//  Shear modulus output params
//	KPMGParams kpmGParams(0.0, 1.0, 1.0, 1.0, 100000, 400); 	//atom
//	KPMGParams kpmGParams(0.0, 1.0, 1.0, 0.1, 1000, 200);		//CG model

	//GDOS-only parameters
	vector<string> gpFiles;

	if(parseInput(argc, argv, kpmParams, kpmCalc, csrFiles, gpFiles))
		return 1;
	kpmParams.readFromFile("test.config");
	kpmGParams.density = kpmParams.density;
	gpFile  = kpmParams.mode == KPMMode::GDOS?"gpGammaDOS.dat":"gpDOS.dat";
	resFile = kpmParams.mode == KPMMode::GDOS?"GammaDOS.dat":"DOS.dat";

	//KPM DOS/GDOS output frequencies
	float wmin = sgn(kpmParams.getEmin())*sqrt(fabs(kpmParams.getEmin()));
	float wmax = sgn(kpmParams.getEmax())*sqrt(fabs(kpmParams.getEmax()));
	Vector freq = arange(kpmGParams.nFreq, sgn(kpmParams.getEmin())*sqrt(fabs(kpmParams.getEmin())), sqrt(kpmParams.getEmax()));
	//G', G'' frequencies
	Vector logfreq = logspace(kpmGParams.wcount, kpmGParams.wmin,kpmGParams.wmax);

	if(kpmParams.mode == KPMMode::GDOS)
	{
		freq = logspace(kpmGParams.nFreq, wmin, wmax,  kpmGParams.wcut);
		if (freq.size() == 0)
		{
			processError("Error: main: Empty frequency vector");
			exit(EXIT_FAILURE);
		}
	}

	//KPM START
	//------------------------------------------------------------------------------------
	processStatus("KPM started");

	int rank, size;
	MPI_Comm comm=MPI_COMM_WORLD;
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
	vector<int> sizes(size);
	vector<int> displacements(size);

	clock_t t;
	clock_t tstart;
	tstart = clock();

	sMatrixPointer hessian;
	KPM::Pointer kpm = nullptr;
	Vector gp  = zeros(kpmParams.getK());
	//Gauss projection vectors calculation/read
	//------------------------------------------------------------------------------------
	if(kpmCalc == KPMCalculation::Sum)
	{
		processStatus("reading coeff files...");
		for (unsigned int i =0; i< gpFiles.size(); ++i)
		{
//			processStatus(gpFiles[i]);
			Vector locgp = zeros(kpmParams.getK());
			fmanager.read(gpFiles[i], locgp);

			gp += locgp(Eigen::seq(0,kpmParams.getK()-1));
		}
		kpm = KPM::Pointer(new KPM(kpmParams, gp));
		fmanager.write("gpSUM.dat",kpm->getCoefficients());
	}
	else
	{

		hessian = std::move(fmanager.readCSR(csrFiles[0], csrFiles[1], csrFiles[2], std::move(hessian), sizes, displacements, comm));
		if (!hessian)
		{
			processStatus("Error while reading CSR");
			return 1;
		}
		processStatus("calculating coeffs...");
		kpm = kpmParams.mode == KPMMode::GDOS ? KPM::Pointer( new KPMGammaDOS(std::move(hessian), kpmParams, sizes, displacements, comm)):
				KPM::Pointer( new KPMDOS(std::move(hessian), kpmParams, sizes, displacements, comm));
	}
	//------------------------------------------------------------------------------------

	if(rank == 0)
	{
		if(kpmCalc == KPMCalculation::Full)
			fmanager.write(gpFile,kpm->getCoefficients());

		processStatus("Sum series started...");
		fmanager.write("freq.dat",freq);
		Vector res = kpm->sumSeries(freq);
		fmanager.write(resFile,freq, res);

		t = clock() - tstart;

		processStatus(string("It took me ")+ to_string(((float)t)/CLOCKS_PER_SEC) +"seconds.");

		if(kpmParams.mode == KPMMode::GDOS)
		{
			ShearModulus smodulus;
			Vector Gp = smodulus.getStorage(kpmGParams, freq, res, logfreq);
			fmanager.write("Gp.dat",logfreq, Gp);
			Vector Gpp = smodulus.getLoss(kpmGParams, freq, res, logfreq);
			fmanager.write("Gpp.dat",logfreq, Gpp);
		}
		//------------------------------------------------------------------------------------
		FILE *stream;
		stream = fopen("time.dat", "a");
		int mpi_size;
		MPI_Comm_size(comm, &mpi_size);
		fprintf(stream, "%d %d %d %f %s\n", kpmParams.getK(), kpmParams.getR(),mpi_size, ((float)t)/CLOCKS_PER_SEC, mem().c_str());
		fclose(stream);
		//------------------------------------------------------------------------------------
	}
	MPI_Finalize();
	return 0;
}

int parseInput(int argc, char* argv[], KPMParams& params, KPMCalculation& kpmCalc,
				vector<string>& csrFiles, vector<string>& gpFiles )
{
	kpmCalc = KPMCalculation::Full;
	int flag;
	int rank = 0;
	MPI_Initialized(&flag);
	if(flag)
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//Reading arguments
		//------------------------------------------------------------------------------------
		options_description all{"Options"};
		options_description necessary{"Necessary"};
		options_description optional{"Optional"};
		try
		{
			necessary.add_options()
		    		("help,h", "Help screen");
			optional.add_options()
					("csr", value<vector<string>>(&csrFiles)->multitoken(), "Input CSR fromatted matrix. data, indices and indptr filenames.")
					("gp", value<vector<string>>(&gpFiles)->multitoken(), "gauss projection files (skip calculation and just sum)");
			all.add(necessary).add(optional);
			variables_map vm;

			store(parse_command_line(argc, argv, all), vm);
			notify(vm);
			if (vm.count("help") || argc == 1)
			{
				argc = 1;

				if(rank == 0)
					std::cout << all << '\n';
				return 1;
			}

			if(vm.count("gp"))
				kpmCalc = KPMCalculation::Sum;
			else
			{
				if( csrFiles.size() == 3 )
				{
					processStatus(string("CSR files: " + csrFiles[0]+ " "+ csrFiles[1]+" "+csrFiles[2]));
				}
				else
				{
					processStatus(string("Error: Please provide 3 files when using --csr: data, indices and indptr."));
					return 1;
				}
			}
			processStatus(string("Parsing input args ended.."));

		}
		catch (const error &ex)
		{
			if(rank == 0)
			{
				std::cerr << ex.what() << '\n';
				std::cout << all << '\n';
			}
			return 1;
		}
		return 0;
}
