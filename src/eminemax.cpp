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

int parseInput(int argc, char* argv[], vector<string>& csrFiles);

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	FileManager fmanager;
	vector<string> csrFiles;

	parseInput(argc, argv, csrFiles);


	//KPM START
	//------------------------------------------------------------------------------------
	processStatus("Find EMin/EMax started");

	//	Eigen::setNbThreads(4);
	clock_t t;
	clock_t tstart;
	tstart = clock();
	sMatrix hessian;
	processStatus(string("main: Reading matrix....mem: ") + mem());
//	if(!justGp)

	fmanager.readCSR(csrFiles[0], csrFiles[1], csrFiles[2], hessian);


	processStatus(string("main: Reading matrix... Finished mem: ")+ mem() );
	FindEminEmax fE;

	float emin = fE.findEmin(hessian);
	float emax = fE.findEmax(hessian);

	cout<<"Emin/Emax: "<<emin << " / "<<emax<<endl;

	FILE *stream;
	stream = fopen("emin_emax.dat", "w");
	fprintf(stream, "%f %f\n",emin, emax );
	MPI_Finalize();
	return 1;
}

int parseInput(int argc, char* argv[], vector<string>& csrFiles)
{

	//Reading arguments
		//------------------------------------------------------------------------------------
		options_description all{"Options"};
		options_description necessary{"Necessary"};
		try
		{

			//		namespace po = boost::program_options;
			necessary.add_options()
		    							  ("help,h", "Help screen")
										  ("csr", value<vector<string>>(&csrFiles)->multitoken()->required(), "Input CSR fromatted matrix. data, indices and indptr filenames.");

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

		return 1;
}
