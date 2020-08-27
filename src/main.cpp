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


int main(int argc, char* argv[])
{

	MPI::Init(argc, argv);

	int K = 1000;
	int R = 20;
	float emin = 0.0f;
	float emax = 0.0f;
	bool find_eminmax = true;
	string affile;

	string gpFile;
	string resFile;
	string mfile;

	float m = 1.0;
	bool mconst = true;

	int kpmmode = 0; // 0 = dos; 1 - gdos;

	//	string fndata;
	//	string fnindptr;
	//	string fnindices;
	vector<string> csrFiles;
	vector<string> gpFiles;
	bool justGp = false;
	FileManager fmanager;
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
					  ("K", value<int>()->default_value(1000), "Set the maximum polynomial  order")
					  ("R", value<int>()->default_value(20), "Set the number of random vectors")
					  ("emin", value<float>(&emin), "Set the minimum eigenvalue (if not set we'll calculate it for you)")
					  ("emax", value<float>(&emax), "Set the maximum eigenvalue")
					  ("mfile", value<string>(), "lammps data file to read masses")
					  ("m", value<float>(), "constant mass value");
		gdos.add_options()
					  ("af", value<string>(), "affine force filename")
					  ("gp", value<vector<string>>(&gpFiles)->multitoken(), "gauss projection files (skip calculation and just sum)");
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
			std::cout << "K: " << vm["K"].as<int>() << '\n';
			K = vm["K"].as<int>();
		}

		if (vm.count("R"))
		{
			std::cout << "R: " << vm["R"].as<int>() << '\n';
			R = vm["R"].as<int>();
		}

		if (vm.count("emin") && vm.count("emax"))
		{
//			emin = vm["emin"].as<float>();
//			emax = vm["emax"].as<float>();
			find_eminmax = false;

		}

		if (vm.count("mode"))
		{
			cout<<"Parsing mode...\n";
			if(vm["mode"].as<string>() == "dos")
				kpmmode = 0;
			else if(vm["mode"].as<string>() == "gdos")
			{
				kpmmode = 1;
				if (vm.count("af") && ( vm.count("mfile") || vm.count("m")))
				{
					affile = vm["af"].as<string>();
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
					cout << "Error: please provide  affine force file(--af) and lammps data file (--mfile or --m for constant mass) for gammaDOS calculation."<<endl;
					return 0;
				}

				if(vm.count("gp"))
					justGp = true;
			}
			else
			{
				cout << "Error: unknown mode"<<endl;
				return 0;
			}

		}
		else
		{
			cout << "Error: Please specify a mode: dos or gdos"<<endl;
			return 0;
		}

		if( csrFiles.size() == 3 )
		{
			//			fndata    = vm["csr"].as<vector<string>>()[0];
			//			fnindices = vm["csr"].as<vector<string>>()[1];
			//			fnindptr  = vm["csr"].as<vector<string>>()[2];

			cout<<"CSR files: "<<csrFiles[0]<< " "<<  csrFiles[1]<<" "<<csrFiles[2]<<endl;
			
		}
		else
		{
			cout << "Error: Please provide 3 files when using --csr: data, indices and indptr."<<endl;
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
	cout<<"KPM started....\n";
	int rank = MPI::COMM_WORLD.Get_rank();
	//	Eigen::setNbThreads(4);
	clock_t t;
	t = clock();
	sMatrix hessian;
	cout<<"main: Reading matrix...."<<"mem: " << mem()<<endl;
	fmanager.readCSR(csrFiles[0], csrFiles[1], csrFiles[2], hessian);
	cout<<"main: Reading matrix... Finished"<<"mem: " << mem()<<endl;
	KPM kpm( hessian, K, R );

	if(find_eminmax)
	{
		//if rank ==0; all the rest wait and then broadcast?
		kpm.findEmin();
		kpm.findEmax();
		emin = kpm.getEmin();
		emax = kpm.getEmax();
		if(rank == 0)
			cout << "Emin Emax calculated: "<<emin<<"   "<<emax<<endl;
	}
	else
	{
		kpm.setEmin( emin );
		kpm.setEmax( emax );
		if(rank == 0)
				cout << "Emin Emax has been set: "<<emin<<"   "<<emax<<endl;
	}

	float Volume =0.0f;
	if(mconst)
		kpm.constMass(m);
	else
	{
		Vector minvSqrt;
		Volume = fmanager.readLAMMPSData(mfile, minvSqrt);
		kpm.setMassVectorInvSqrt(minvSqrt);
	}

	kpm.HTilde();



	//	Vector gp = kpm.getCoeffDOS();
	kpm.setR(R);

	Vector gp  = zeros(kpm.getK());
	if(!kpmmode)
	{
		gp = kpm.getCoeffDOS();
		gpFile = "gpDOS.dat";
		resFile = "DOS.dat";
	}
	else
	{
		Vector af;
		fmanager.readAF(affile, af);
		kpm.setAF(af);
		if(rank == 0)
			cout << "gdos mode:"<<endl;
		gpFile = "gpGammaDOS.dat";
		resFile = "GammaDOS.dat";
		if(!justGp)
		{
			gp = kpm.getCoeffGammaDOS();
		}
		else
		{

			for (unsigned int i =0; i< gpFiles.size(); ++i)
			{
				Vector locgp = zeros(kpm.getK());
				fmanager.read(gpFiles[i], locgp);
				gp += locgp;
			}
		}

	}

	if(rank == 0)
	{

		Vector freq = arange(4000, sgn(emin)*sqrt(fabs(emin)), sqrt(emax));
		//		Vector dos = kpm.sumSeries(freq, gp);
		Vector res = kpm.sumSeries(freq, gp);
		//		kpm.write("gP.dat",gp);
		//		kpm.write("DOS.dat",freq, dos);

		fmanager.write(gpFile,gp);
		fmanager.write(resFile,freq, res);
		t = clock() - t;

		printf ("It took me %d clicks (%f seconds).\n",(int) t,((float)t)/CLOCKS_PER_SEC);
		FILE *stream;
		stream = fopen("time.dat", "a");
		fprintf(stream, "%d %d %d %f\n", K, R, (int) t, ((float)t)/CLOCKS_PER_SEC);

		if(kpmmode)
		{
			Vector logfreq = logspace(100, 0.01,1000);
			Vector Gp = kpm.getModulus(97.0, Volume, freq, res, logfreq );
			fmanager.write("Gp.dat",logfreq, Gp);
			Vector Gpp = kpm.getModulusImag(97.0, Volume, freq, res, logfreq );
			fmanager.write("Gpp.dat",logfreq, Gpp);
		}
	}


	MPI::Finalize();
	return 0;
}
