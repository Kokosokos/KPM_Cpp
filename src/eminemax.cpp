//============================================================================
// Name        : KPM.cpp
// Author      : IVAN
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

//Parse input arguments
#include <boost/program_options.hpp>
using namespace boost::program_options;

#include "EminEmaxFinder.h"

int parseInput(int argc, char* argv[], vector<string>& csrFiles);
//vector<double> findEminEmax(const vector<string>& csrFiles);

int main(int argc, char* argv[])
{

	vector<string> csrFiles;
	if (!parseInput(argc, argv, csrFiles))
	{
		return 1;
	}

	EminEmaxFinder finder;
	vector<double> e_limits = finder.findEminEmax(csrFiles);
	if (e_limits[1] < e_limits[0])
	{
		return 1;
	}

	FILE *stream;
	stream = fopen("emin_emax.dat", "w");
	fprintf(stream, "%f %f\n", e_limits[0], e_limits[1] );
	fclose(stream);
	return 0;
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
