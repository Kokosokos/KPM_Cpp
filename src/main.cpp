//============================================================================
// Name        : KPM.cpp
// Author      : IVAN
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

#include "KPM.h"
//!!!! Implement ZERO FREQ SHEAR MODULUS output!!!
//!
//!
using namespace std;


#include <Eigen/Core>
#include <Eigen/SparseCore>


//Parse input arguments
#include <boost/program_options.hpp>
using namespace boost::program_options;

//struct mode
//{
//	mode(std::string const& val):
//		value(val)
//	{ }
//	std::string value;
//};
//
//void validate(boost::any& v,
//		std::vector<std::string> const& values,
//		mode* target_type,
//		int)
//{
//	using namespace boost::program_options;
//
//	// Make sure no previous assignment to 'v' was made.
//	validators::check_first_occurrence(v);
//
//	// Extract the first string from 'values'. If there is more than
//	// one string, it's an error, and exception will be thrown.
//	std::string const& s = validators::get_single_string(values);
//
//	if (s == "dos" || s == "gdos")
//	{
//		v = boost::any(mode(s));
//	}
//	else
//	{
//		throw validation_error(validation_error::invalid_option_value);
//	}
//}



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
			  ("emin", value<float>(), "Set the minimum eigenvalue (if not set we'll calculate it for you)")
			  ("emax", value<float>(), "Set the maximum eigenvalue")
			  ("mfile", value<string>(), "lammps data file to read masses")
			  ("m", value<float>(), "constant mass value");
		gdos.add_options()
			  ("af", value<string>(), "affine force filename");
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
			emin = vm["emin"].as<float>();
			emax = vm["emax"].as<float>();
			find_eminmax = false;

		}

		if (vm.count("mode"))
		{
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
	int rank = MPI::COMM_WORLD.Get_rank();
	//	Eigen::setNbThreads(4);
	clock_t t;
	t = clock();

	KPM kpm( csrFiles, K, R );

	if(find_eminmax)
	{
		//if rank ==0; all the rest wait and then broadcast?
		kpm.findEmin();
		kpm.findEmax();
		cout << "Emin Emax calculation: "<<kpm.m_emin<<"   "<<kpm.m_emax<<endl;
	}
	else
	{
		kpm.m_emin = emin;
		kpm.m_emax = emax;
	}

	if(mconst)
		kpm.constMass(m);
	else
		kpm.readLAMMPSData(mfile);

	kpm.HTilde();



	//	Vector gp = kpm.getCoeffDOS();
	kpm.setR(R);

	Vector gp;
	if(!kpmmode)
	{
		gp = kpm.getCoeffDOS();
		gpFile = "gpDOS.dat";
		resFile = "DOS.dat";
	}
	else
	{
		gp = kpm.getCoeffGammaDOS();
		gpFile = "gpGammaDOS.dat";
		resFile = "GammaDOS.dat";
		kpm.readAF(affile);
	}
	if(rank == 0)
	{
		Vector freq = arange(400, sgn(kpm.m_emin)*sqrt(fabs(kpm.m_emin)), sqrt(kpm.m_emax));
		//		Vector dos = kpm.sumSeries(freq, gp);
		Vector res = kpm.sumSeries(freq, gp);
		//		kpm.write("gP.dat",gp);
		//		kpm.write("DOS.dat",freq, dos);

		kpm.write(gpFile,gp);
		kpm.write(resFile,freq, res);
		t = clock() - t;

		printf ("It took me %d clicks (%f seconds).\n",(int) t,((float)t)/CLOCKS_PER_SEC);
		FILE *stream;
		stream = fopen("time.dat", "a");
		fprintf(stream, "%d %d %d %f\n", K, R, (int) t, ((float)t)/CLOCKS_PER_SEC);
	}




	MPI::Finalize();
	return 0;
}
