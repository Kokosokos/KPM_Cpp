/*
 * FileManager.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: ivan
 */

#include "FileManager.h"
#include <fstream>
#include <sstream>

#include <algorithm>
#include <iterator>

#include <Eigen/Core>
#include <Eigen/SparseCore>
int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}
int memInt(){ //Note: this value is in MB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result/1024.0;
}
string mem()
{
	return to_string(memInt());
}
//std::string mem()
//{
//
//    const std::string info[] = {"Cached:", "Buffers:", "MemFree:", "MemTotal:"};
//    int intInfo[4];
//
//    std::string token;
//    std::ifstream file("/proc/meminfo");
//
//    while(file >> token){
//
//        for(short i = 4; i != -1; --i)
//        {
//            if(token == info[i])
//            {
//                file >> intInfo[i];
//
//                if(i == 0){
//                    file.close();
//                    return std::to_string((intInfo[3] - intInfo[2] - (intInfo[1] + intInfo[0])) / 1024) + "m ";
//                }
//
//            }
//        }
//
//       // ignore rest of the line
//        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    }
//
//
//    // Couldn't get a reading!
//    return "...";
//}

FileManager::FileManager() {
	// TODO Auto-generated constructor stub

}

FileManager::~FileManager() {
	// TODO Auto-generated destructor stub
}

void FileManager::write(string filename, const Vector&  v1, const Vector&  v2)
{
	FILE *stream;
	stream = fopen(filename.c_str(), "w");
	for(int i = 0; i< v1.size(); ++i )
	{
		fprintf(stream, "%f %f\n", v1[i], v2[i]);
	}
	fclose(stream);
}

void FileManager::write(string filename, const Vector&  v1)
{
	FILE *stream;
	stream = fopen(filename.c_str(), "w");
	for(int i = 0; i< v1.size(); ++i )
	{
		fprintf(stream, "%f\n", v1[i]);
	}
	fclose(stream);
}

void FileManager::read(string filename, Vector& v1)
{
	FILE *stream;
	stream = fopen(filename.c_str(), "r");
	if (stream==NULL) perror ("Error opening file for AF");
	float val = 0.0f;
	vector<double> v;
	while(fscanf(stream, "%f", &val) != EOF)
	{
		v.push_back(val);
	}
	fclose(stream);
	//	m_af = Vector(v.data());
	//	double* ptr = &v[0];
	v1 = Vector::Map(v.data(), v.size());
}
void  FileManager::readAF(string filename, Vector& af)
{
	read(filename, af);
	//	af = m_af.cwiseProduct(m_MinvSqrt);
	//	m_af = my_vect;
}


float FileManager::readLAMMPSData(string filename, Vector& minvSqrt)
{
	unsigned int curLine = 0;


	std::ifstream fileInput;
	string line;
	fileInput.open(filename.c_str());


	//Search for N atoms
	//	string search = "atoms";
	int nM = 0;
	int N=0; // number of atoms
	vector<double> masses;
	vector<int> massIds;
	vector<double> massesFull;
	float Vol = 0.0f;
	float Lx = 0.0f;
	float Ly = 0.0f;
	float Lz = 0.0f;
	while(getline(fileInput, line))
	{
		curLine++;

		if (line.find("atoms", 0) != string::npos)
		{
			std::istringstream iss(line);

			std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
					std::istream_iterator<std::string>());
			iss =  std::istringstream(results[0]);
			iss >> N;
		}

		if (line.find("atom types", 0) != string::npos)
		{
			std::istringstream iss(line);

			std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
					std::istream_iterator<std::string>());

			iss =  std::istringstream(results[0]);
			iss >> nM;
		}



		if (line.find("xlo xhi", 0) != string::npos)
		{
			float xlo =0.0f;
			float xhi =0.0f;
			std::istringstream iss(line);

			std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
					std::istream_iterator<std::string>());

			iss =  std::istringstream(results[0]);
			iss >> xlo;
			iss =  std::istringstream(results[1]);
			iss >> xhi;
			Lx = xhi - xlo;
		}
		if (line.find("ylo yhi", 0) != string::npos)
		{
			float ylo =0.0f;
			float yhi =0.0f;
			std::istringstream iss(line);

			std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
					std::istream_iterator<std::string>());

			iss =  std::istringstream(results[0]);
			iss >> ylo;
			iss =  std::istringstream(results[1]);
			iss >> yhi;
			Ly = yhi - ylo;
		}
		if (line.find("zlo zhi", 0) != string::npos)
		{
			float zlo =0.0f;
			float zhi =0.0f;
			std::istringstream iss(line);

			std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
					std::istream_iterator<std::string>());

			iss =  std::istringstream(results[0]);
			iss >> zlo;
			iss =  std::istringstream(results[1]);
			iss >> zhi;
			Lz = zhi - zlo;
		}



		if (line.find("Masses", 0) != string::npos)
		{
			getline(fileInput, line);
			float m=0.0f;
			for (int i =0; i < nM; ++i)
			{
				getline(fileInput, line);
				std::istringstream iss(line);

				std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
						std::istream_iterator<std::string>());

				iss =  std::istringstream(results[1]);
				iss>>m;
				masses.push_back(m);
			}

		}

		if (line.find("Atoms", 0) != string::npos)
		{
			getline(fileInput, line);

			int mid=0;
			for (int i =0; i < N; ++i)
			{
				getline(fileInput, line);
				std::istringstream iss(line);

				std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
						std::istream_iterator<std::string>());

				iss =  std::istringstream(results[2]);
				iss>>mid;
				massIds.push_back(mid);

				//Dimensionality == 3
				double minvsqrt = 1.0 / sqrt(masses[mid-1]);
				massesFull.push_back(minvsqrt);
				massesFull.push_back(minvsqrt);
				massesFull.push_back(minvsqrt);
			}
			break;
		}
	}
	//	m_M = Vector::Map(massesFull.data(), massesFull.size());
	minvSqrt = Vector::Map(massesFull.data(), massesFull.size());
	Vol = Lx* Ly*Lz;
	if (Vol == 0.0f)
	{
		std::cout<<"Warning: Can't read box size from lammps data file (or it is zero, or it is 2d simulation)"<<std::endl;
	}

	//Search for masses values


	fileInput.close();
	return Vol;
}

void FileManager::readCSR(string fdata, string findices, string findptr, sMatrix& hessian)
{
	//Read indptr from CSR matrix (== cumulative number of nonzero elements in a row)
	std::cout<<"Reading indptr..." << "mem: " << mem() << std::endl;

	vector<long int> indptr;
	FILE *stream;
	stream = fopen(findptr.c_str(), "r");
	if (stream==NULL) perror ("Error opening file for indptr");

	long int val;
	while(fscanf(stream, "%ld", &val) != EOF)
	{
		indptr.push_back(val);
	}
	fclose(stream);
	unsigned int N=indptr.size()-1;

	int DOF = N;

	//Read data and column indices
	long int nNon0 = *(indptr.end()-1); //number of non zero elements

	std::cout<<"Reading data..."<<"mem: " << mem()<<"; nonzeros "<<nNon0<<std::endl;
	std::ifstream ifile3(fdata.c_str(), std::ios::in);
	if (!ifile3.is_open()) {
        std::cerr << "There was a problem opening the data file!\n";
        exit(1);//exit or do additional error checking
    }
	std::ifstream ifile2(findices.c_str(), std::ios::in);
	if (!ifile2.is_open()) {
        std::cerr << "There was a problem opening the indices file!\n";
        exit(1);//exit or do additional error checking
    }
//	FILE *stream3;
//	stream3 = fopen(fdata.c_str(), "r");
//	FILE *stream2;
//	stream2 = fopen(findices.c_str(), "r");


	double dataval=0.0;
	int indval=0;
	int rowLen = 0;

	//Create sparse matrix
	std::cout<<"Creating sparse matrix..."<<std::endl;
	hessian = sMatrix(N,N);
	// Reserving enough space for non-zero elements

	std::cout<<"Reserving sparse matrix space..."<<"mem: " << mem()<<std::endl;
	hessian.reserve( nNon0 );
	std::cout<<"Reserving sparse matrix space...finished"<<"mem: " << mem()<<std::endl;
	vector<double> vdata;
	vector<long int> vindices;
	for (unsigned int i =0; i < N ;++i)
	{
		rowLen = indptr[i+1] - indptr[i];

		hessian.startVec(i);
		for (int j =0;j <rowLen;++j)
		{
			//if(fscanf(stream3, "%f", &dataval) == EOF)  perror (("Error: datafile["+ fdata +"] has too few elements").c_str());
			//if(fscanf(stream2, "%d", &indval) == EOF)  perror (("Error: indicesfile["+ findices +"] has too few elements (must be "+to_string(nNon0)+")").c_str());
//			fscanf(stream3, "%lf", &dataval);
//			fscanf(stream2, "%ld", &indval);
			ifile3 >> dataval;
			ifile2 >> indval;
//			if(i > 32000)
//			{
			//	vdata.push_back(dataval);
			//	vindices.push_back(indval);
//			}
			//if(i==31919)
			//	std::cout<<"Reading "<<j<<"th element..." << "; (value, index) = ("<<dataval<<", "<<indval<< "); mem: " << mem() << std::endl;
//			hessian.coeffRef(i, indval-1) = dataval;	//		hessian.insertBack( i, indval-1) =  dataval ;
			hessian.insertBack( i, indval-1) =  dataval ;
//			hessian.insert( i, indval-1) =  dataval ;
		}
		if( i % 1000 == 0)
			std::cout<<"Reading "<<i<<"th row..." << "; (value, index) = ("<<dataval<<", "<<indval<< "); mem: " << mem() << std::endl;
	}
	hessian.finalize();
	std::cout<<"Outer index size: "<<sizeof(*hessian.outerIndexPtr())<<std::endl;
	std::cout<<"Inner index size: "<<sizeof(*hessian.innerIndexPtr())<<std::endl;
	std::cout<<"Reading csr matrix finished..." << "mem: " << mem() << std::endl;
//	fclose(stream2);
//	fclose(stream3);
	//	m_hessian.makeCompressed();
	//get 1 element

}


