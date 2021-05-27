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
//int main(int argc, char* argv[])
//{
//
//	MPI_Init(&argc, &argv);
//	MPI_Finalize();
//	cout<<"Test::\n";
//	return 0;
//}

//int main2()
//{
//	Vector v(7);
//	v<<0.2,0.3,0.1,1.5,0.0,11,0.3;
//
//	cout<<v.array()<<endl;
//	cout<<"----------"<<endl;
////	cout<<(v - v.cwiseProduct(Vector(v.array()>0.5)))<<endl;
//	Vector B = Vector(v.array()>0.5);
//	B.template cast<int>();
//	cout<<(v*B)<<endl;
//}
int main(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	int K = 1000;
	int R = 20;
	float emin = 0.0f;
	float emax = 0.0f;
	float GA = 97.0; //affine shear modulus
	bool find_eminmax = true;
	string affile;

	string gpFile;
	string resFile;
	string mfile;

	float m = 1.0;
	float epsilon =0.05;
	bool mconst = true;

	int kpmmode = 0; // 0 = dos; 1 - gdos;
	string kernel = "jk";
	int lkernel=4;
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
									  ("e", value<float>()->default_value(0.05), "Set the epsilon value")
									  ("kernel", value<string>()->default_value("jk"), "Choose kernel")
									  ("l", value<int>()->default_value(4), "Choose kernel parameter (if using Lorentz kernel)")
									  ("m", value<float>(), "constant mass value")
									  ("gp", value<vector<string>>(&gpFiles)->multitoken(), "gauss projection files (skip calculation and just sum)");
		gdos.add_options()
									  ("af", value<string>(), "affine force filename")
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
			processStatus(string( "K: " +  vm["K"].as<int>()));
			K = vm["K"].as<int>();
		}

		if (vm.count("R"))
		{
			processStatus(string( "R: " + vm["R"].as<int>() ));
			R = vm["R"].as<int>();
		}
		if (vm.count("e"))
		{
			processStatus(string( "epsilon: ") +  to_string(vm["e"].as<float>()));
			epsilon = vm["e"].as<float>();
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
			//			emin = vm["emin"].as<float>();
			//			emax = vm["emax"].as<float>();
			find_eminmax = false;

		}

		if (vm.count("mode"))
		{
			processStatus(string( "Parsing mode..."));
			if(vm.count("gp"))
				justGp = true;
			if(vm["mode"].as<string>() == "dos")
				kpmmode = 0;
			else if(vm["mode"].as<string>() == "gdos")
			{
				kpmmode = 1;
				if (vm.count("af") && vm.count("GA") && ( vm.count("mfile") || vm.count("m")))
				{
					affile = vm["af"].as<string>();
					GA = vm["GA"].as<float>();
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
			//			fndata    = vm["csr"].as<vector<string>>()[0];
			//			fnindices = vm["csr"].as<vector<string>>()[1];
			//			fnindptr  = vm["csr"].as<vector<string>>()[2];

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
	//------------------------------------------------------------------------------------


	//KPM START
	//------------------------------------------------------------------------------------
	processStatus("KPM started");

	int rank;
	MPI_Comm comm=MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);
	//	Eigen::setNbThreads(4);
	clock_t t;
	clock_t tstart;
	tstart = clock();
	sMatrix hessian;
	processStatus(string("main: Reading matrix....mem: ") + mem());
	if(!justGp)
		fmanager.readCSR(csrFiles[0], csrFiles[1], csrFiles[2], hessian);
	processStatus(string("main: Reading matrix... Finished mem: ")+ mem() );
	KPM kpm( hessian, K, R , epsilon, comm, kernel, lkernel);
	//	if(!justGp)
	//	{
	if(find_eminmax)
	{
		//if rank ==0; all the rest wait and then broadcast?
		if(!kpm.findEmax()) return 0;
		if(!kpm.findEmin()) return 0;

		emax = kpm.getEmax();
		emin = kpm.getEmin();

		processStatus( string( "Emin Emax calculated: ") + to_string(emin) + "   " + to_string(emax) );
	}
	else
	{
		kpm.setEmin( emin );
		kpm.setEmax( emax );
		if(rank == 0)
			processStatus( string( "Emin Emax has been set: ") + to_string(emin) + "   " + to_string(emax) );
	}

	kpm.HTilde();
	//	}
	float Volume = 0.0f;
	if(mconst)
		kpm.constMass(m);
	else
	{
		Vector minvSqrt;
		Volume = fmanager.readLAMMPSData(mfile, minvSqrt);
		kpm.setMassVectorInvSqrt(minvSqrt);

	}

	t = clock() - tstart;
	processStatus(string("It took me ")+ to_string(((float)t)/CLOCKS_PER_SEC) +"seconds.");
	processStatus(string("main: HTilde..start  mem: ") + mem() );




	processStatus(string("main: HTilde..end  mem: ") + mem() );


	//	Vector gp = kpm.getCoeffDOS();
	kpm.setR(R);

	Vector gp  = zeros(kpm.getK());

	gpFile  = kpmmode?"gpGammaDOS.dat":"gpDOS.dat";
	resFile = kpmmode?"GammaDOS.dat":"DOS.dat";

	if(justGp)
	{
		processStatus("reading coeff files...");
		for (unsigned int i =0; i< gpFiles.size(); ++i)
		{
			cout<<" "<<gpFiles[i]<<flush;
			Vector locgp = zeros(kpm.getK());
			fmanager.read(gpFiles[i], locgp);

			gp += locgp(Eigen::seq(0,K-1));
		}
		cout<<"\n";
	}
	else
	{
		processStatus("calculating coeffs...");
		if(kpmmode)
		{
			Vector af;
			fmanager.readAF(affile, af);
			kpm.setAF(af);
		}
		gp = kpmmode?kpm.getCoeffGammaDOS():kpm.getCoeffDOS();
	}
	if(rank == 0)
	{
		if(!justGp)
			fmanager.write(gpFile,gp);
		Vector freq = arange(4000, sgn(emin)*sqrt(fabs(emin)), sqrt(emax));
		if(kpmmode)
		{
			Vector neg,pos;
			//			neg = -1.0*logspace(int(fabs(emin)),-2, log10(sqrt(fabs(emin))));
			//			pos = logspace(int(emax), -2, log10(sqrt(emax)));
			//			cout<<"Neg freq\n"<<flush;
			neg = -1.0*logspace(int(fabs(emin)),0.01, sqrt(fabs(emin)));
			//			cout<<"Pos freq\n"<<flush;
			pos = logspace(int(emax), 0.01, sqrt(emax));
			//			cout<<"Tot freq\n"<<flush;
			freq = Vector(neg.size() + pos.size());
			freq <<neg.reverse(),pos;

			//			freq = np.concatenate([-np.logspace(-2,np.log10(np.sqrt(np.abs(EStart))),np.abs(EStart))[::-1],np.logspace(-2,np.log10(np.sqrt(EEnd)),np.abs(EEnd))]);

		}
		processStatus("Sum series started...");
		Vector res = kpm.sumSeries(freq, gp);

		fmanager.write(resFile,freq, res);
		fmanager.write("freq.dat",freq);
		t = clock() - tstart;

		processStatus(string("It took me ")+ to_string(((float)t)/CLOCKS_PER_SEC) +"seconds.");
		FILE *stream;
		stream = fopen("time.dat", "a");
		fprintf(stream, "%d %d %d %f\n", K, R, (int) t, ((float)t)/CLOCKS_PER_SEC);

		if(kpmmode)
		{
			Vector logfreq = logspace(200, 0.01,1000);
			Vector Gp = kpm.getModulus(GA, Volume, freq, res, logfreq );
			fmanager.write("Gp.dat",logfreq, Gp);
			Vector Gpp = kpm.getModulusImag(97.0, Volume, freq, res, logfreq );
			fmanager.write("Gpp.dat",logfreq, Gpp);
		}
	}


	MPI_Finalize();
	return 0;
}
