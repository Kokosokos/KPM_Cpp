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
	//	vector<int> T(100000, 22);
	vector<int> indptr;
	FILE *stream;
	stream = fopen(findptr.c_str(), "r");
	if (stream==NULL) perror ("Error opening file for indptr");

	int val;
	while(fscanf(stream, "%d", &val) != EOF)
	{
		indptr.push_back(val);
	}
	fclose(stream);
	unsigned int N=indptr.size()-1;
	//	cout<<"N:"<<N<<endl;

	int DOF = N;

	//Read data and column indices
	int nNon0 = *(indptr.end()-1); //number of non zero elements

	FILE *stream3;
	stream3 = fopen(fdata.c_str(), "r");
	float dataval=0.0f;
	vector <float> data;
	for (int i =0; i < nNon0;++i)
	{
		if(fscanf(stream3, "%f", &dataval) == EOF)  perror ("Error: datafile has too few elements");
		data.push_back(dataval);
	}
	fclose(stream3);

	FILE *stream2;
	stream2 = fopen(findices.c_str(), "r");
	int indval=0;
	vector <int> indices;
	for (int i =0; i < nNon0;++i)
	{
		if(fscanf(stream, "%d", &indval) == EOF)  perror ("Error: datafile has too few elements");
		indices.push_back(indval);
	}
	fclose(stream2);
	int rowLen = 0;
	int nnonzero = indptr[N];

	//Create sparse matrix
	hessian = sMatrix(N,N);
	// Reserving enough space for non-zero elements



	vector<int> sizes(N);
	for (unsigned int i =0; i < N ;++i)
	{
		sizes[i]=indptr[i+1] - indptr[i];
	}
	hessian.reserve( sizes );
	for (unsigned int i =0; i < N ;++i)
	{
		rowLen = indptr[i+1] - indptr[i];


		for (int j =0;j <rowLen;++j)
		{
			int k = indptr[i] + j;
			hessian.insert( i, indices[k]-1) =  data[k] ;
		}
	}
	//	m_hessian.makeCompressed();
	//get 1 element
	//	cout<<m_hessian.coeff(1,1);

}
