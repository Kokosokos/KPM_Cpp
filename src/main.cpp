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

int parseInput(int argc, char* argv[], KPMMode& kpmmode, KPMParams& params, KPMGParams& kpmGParams, KPMCalculation& kpmCalc,
		vector<string>& csrFiles, vector<string>& gpFiles,
		string& affile, string& mfile, float& m, bool& mconst );

int main(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	FileManager fmanager;
	vector<string> csrFiles;
	string gpFile;
	string resFile;

	KPMMode kpmMode = KPMMode::DOS;
	KPMParams kpmParams;
	KPMCalculation kpmCalc;
	//Shear modulus output params
	KPMGParams kpmGParams(0.0, 1.0, 1.0, 1.0, 100000, 400); //atom
//	KPMGParams kpmGParams(0.0, 1.0, 1.0, 0.1, 1000, 200); //CG model

	//GDOS-only parameters
	string affile;
	string mfile;
	float m = 1.0;
	bool mconst = true;

	vector<string> gpFiles;

	if(!parseInput(argc, argv, kpmMode, kpmParams, kpmGParams, kpmCalc,
				csrFiles, gpFiles,
				affile, mfile, m, mconst ))
			return 0;
	gpFile  = kpmMode == KPMMode::GDOS?"gpGammaDOS.dat":"gpDOS.dat";
	resFile = kpmMode == KPMMode::GDOS?"GammaDOS.dat":"DOS.dat";

	//KPM DOS/GDOS output frequencies
	Vector freq = arange(4000, sgn(kpmParams.getEmin())*sqrt(fabs(kpmParams.getEmin())), sqrt(kpmParams.getEmax()));
	//G', G'' frequencies
	Vector logfreq = logspace(kpmGParams.getNPoints(), kpmGParams.getWmin(),kpmGParams.getWmax()); //atom
	if(kpmMode == KPMMode::GDOS)
	{
		Vector neg,pos;
		neg = -1.0*logspace(int(fabs(kpmParams.getEmin())),0.001, sqrt(fabs(kpmParams.getEmin())));
		pos = logspace(int(kpmParams.getEmax()), 0.001, sqrt(kpmParams.getEmax()));

		freq = Vector(neg.size() + pos.size());
		freq <<neg.reverse(),pos;

	}


	//KPM START
	//------------------------------------------------------------------------------------
	processStatus("KPM started");

	int rank, size;
	MPI_Comm comm=MPI_COMM_WORLD;
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();

	clock_t t;
	clock_t tstart;
	tstart = clock();
	sMatrixPointer hessian;

	vector<int> sizes(size);
	vector<int> displacements(size);

	hessian = std::move(fmanager.readCSR(csrFiles[0], csrFiles[1], csrFiles[2], std::move(hessian), sizes, displacements, comm));
	KPM kpm( std::move(hessian), kpmParams, sizes, displacements, comm);

	if(mconst)
		kpm.constMass(m);
	else
	{
		Vector minvSqrt;
		kpmGParams.setVolume( fmanager.readLAMMPSData(mfile, minvSqrt));
		kpm.setMassVectorInvSqrt(minvSqrt);
	}

	//Gauss projection vectors calculation/read
	//------------------------------------------------------------------------------------
	Vector gp  = zeros(kpmParams.getK());

	if(kpmCalc == KPMCalculation::Sum)
	{
		processStatus("reading coeff files...");
		for (unsigned int i =0; i< gpFiles.size(); ++i)
		{
			cout<<" "<<gpFiles[i]<<flush;
			Vector locgp = zeros(kpmParams.getK());
			fmanager.read(gpFiles[i], locgp);

			gp += locgp(Eigen::seq(0,kpmParams.getK()-1));
		}
		cout<<"\n";
	}
	else
	{
		processStatus("calculating coeffs...");
		if(kpmMode == KPMMode::GDOS)
		{
			Vector af;
			fmanager.readAF(affile, af);
			kpm.setAF(af);
		}
		gp = kpmMode == KPMMode::GDOS?kpm.getCoeffGammaDOS():kpm.getCoeffDOS();
	}

//	MPI_Barrier(comm);
//	return 1;
	if(rank == 0)
	{
		if(kpmCalc == KPMCalculation::Full)
			fmanager.write(gpFile,gp);

		processStatus("Sum series started...");
		Vector res = kpm.sumSeries(freq, gp);

		fmanager.write(resFile,freq, res);
		fmanager.write("freq.dat",freq);
		t = clock() - tstart;

		processStatus(string("It took me ")+ to_string(((float)t)/CLOCKS_PER_SEC) +"seconds.");
		FILE *stream;
		stream = fopen("time.dat", "a");
		int mpi_size;
		MPI_Comm_size(comm, &mpi_size);
		fprintf(stream, "%d %d %d %f %s\n", kpmParams.getK(), kpmParams.getR(),mpi_size, ((float)t)/CLOCKS_PER_SEC, mem().c_str());
		fclose(stream);
		if(kpmMode == KPMMode::GDOS)
		{
			Vector Gp = kpm.getModulus(kpmGParams.getGA(), kpmGParams.getVolume(), freq, res, logfreq, kpmGParams.getFriction());
			fmanager.write("Gp.dat",logfreq, Gp);
			Vector Gpp = kpm.getModulusImag(kpmGParams.getGA(), kpmGParams.getVolume(), freq, res, logfreq, kpmGParams.getFriction() );
			fmanager.write("Gpp.dat",logfreq, Gpp);
		}
	}


	MPI_Finalize();
	return 0;
}

int parseInput(int argc, char* argv[], KPMMode& kpmmode, KPMParams& params, KPMGParams& kpmGParams, KPMCalculation& kpmCalc,
				vector<string>& csrFiles, vector<string>& gpFiles,
				string& affile, string& mfile, float& m, bool& mconst )
{
	int K = 1000;
	int R = 20;
	float epsilon = 0.05;
	float emin = 0.0f;
	float emax = 0.0f;
	kpmCalc = KPMCalculation::Full;
	string kernel = "jk";
	int lkernel=4;
	//Reading arguments
		//------------------------------------------------------------------------------------
		options_description all{"Options"};
		options_description necessary{"Necessary"};
		options_description optional{"Optional"};
		options_description gdos{"GammaDOS(--gdos) specific"};
		try
		{

			//		namespace po = boost::program_options;
			necessary.add_options()
		    							  ("help,h", "Help screen")
										  ("csr", value<vector<string>>(&csrFiles)->multitoken()->required(), "Input CSR fromatted matrix. data, indices and indptr filenames.")
										  ("mode", value<string>()->required(), "set mode: dos or gdos");
			optional.add_options()
										  ("K", value<int>(&K)->default_value(1000), "Set the maximum polynomial  order")
										  ("R", value<int>(&R)->default_value(20), "Set the number of random vectors")
										  ("emin", value<float>(&emin), "Set the minimum eigenvalue (if not set we'll calculate it for you)")
										  ("emax", value<float>(&emax), "Set the maximum eigenvalue")
										  ("mfile", value<string>(), "lammps data file to read masses")
										  ("e", value<float>(&epsilon)->default_value(0.05), "Set the epsilon value")
										  ("kernel", value<string>()->default_value("jk"), "Choose kernel")
										  ("l", value<int>()->default_value(4), "Choose kernel parameter (if using Lorentz kernel)")
										  ("m", value<float>(), "constant mass value")
										  ("gp", value<vector<string>>(&gpFiles)->multitoken(), "gauss projection files (skip calculation and just sum)");
			gdos.add_options()
										  ("af", value<string>(), "affine force filename")
										  ("nu", value<float>(), "friction coeff")
										  ("GA", value<float>(), "affine shear modulus");

			all.add(necessary).add(optional).add(gdos);
			variables_map vm;

			store(parse_command_line(argc, argv, all), vm);
			notify(vm);
			if (vm.count("help") || argc == 1)
			{
				argc = 1;
				std::cout << all << '\n';
				return 0;
			}

			if (vm.count("K"))
			{
				processStatus(string( "K: " +  to_string(K)));

			}

			if (vm.count("R"))
			{
				processStatus(string( "R: " + to_string(R) ));
			}
			if (vm.count("e"))
			{
				processStatus(string( "epsilon: ") +  to_string(vm["e"].as<float>()));
//				epsilon = vm["e"].as<float>();
			}
			if (vm.count("kernel"))
			{
				processStatus(string( "kernel: " +  vm["kernel"].as<string>()));
				kernel = vm["kernel"].as<string>();
				if (vm.count("l"))
				{
					processStatus(string( "l: " + vm["l"].as<int>() ));
					lkernel = vm["l"].as<int>();
				}

			}
			if (vm.count("emin") && vm.count("emax"))
			{
				params.setEminEmax(emin, emax);
			}
			else
			{
				processStatus(string( "Error: please provide emin/emax. (Use eminemax tool from the same 'package')"));
				return 0;
			}


			if (vm.count("mode"))
			{
				processStatus(string( "Parsing mode..."));
				if(vm.count("gp"))
					kpmCalc = KPMCalculation::Sum;
				if(vm["mode"].as<string>() == "dos")
					kpmmode = KPMMode::DOS;
				else if(vm["mode"].as<string>() == "gdos")
				{
					kpmmode = KPMMode::GDOS;
					if (vm.count("af") && vm.count("GA") && ( vm.count("mfile") || vm.count("m")))
					{
						affile = vm["af"].as<string>();
						kpmGParams.setGA(vm["GA"].as<float>());
						if (vm.count("nu"))
							kpmGParams.setFriction(vm["nu"].as<float>());
						if(vm.count("mfile"))
						{
							mfile = vm["mfile"].as<string>();
							mconst = false;
						}
						else
						{
							m = vm["m"].as<float>();
							mconst = true;
						}

					}
					else
					{
						processStatus(string( "Error: please provide  affine force file(--af), affine shear modulus(--GA) and lammps data file (--mfile or --m for constant mass) for gammaDOS calculation."));
						return 0;
					}


				}
				else
				{
					processStatus(string( "Error: unknown mode"));
					return 0;
				}

			}
			else
			{
				processStatus(string("Error: Please specify a mode: dos or gdos"));
				return 0;
			}

			if( csrFiles.size() == 3 )
			{
				processStatus(string("CSR files: " + csrFiles[0]+ " "+ csrFiles[1]+" "+csrFiles[2]));
			}
			else
			{
				processStatus(string("Error: Please provide 3 files when using --csr: data, indices and indptr."));
				return 0;
			}
			processStatus(string("Parsing input args ended.."));

		}
		catch (const error &ex)
		{
			std::cerr << ex.what() << '\n';
			std::cout << all << '\n';
			return 0;
		}
		params.setK(K);
		params.setR(R);
		params.setEpsilon(epsilon);
		if(kernel == "jk")
			params.setKernel(KPMKernels::Jackson);
		if(kernel == "lk")
		{
			params.setKernel(KPMKernels::Lorentz);
			params.setLKernel(lkernel);
		}
		return 1;
}
