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
		fprintf(stream, "%.8f %.8f\n", v1[i], v2[i]);
	}
	fclose(stream);
}

void FileManager::write(string filename, const Vector&  v1)
{
	FILE *stream;
	stream = fopen(filename.c_str(), "w");
	for(int i = 0; i< v1.size(); ++i )
	{
		fprintf(stream, "%.8f\n", v1[i]);
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
}

VectorPointer  FileManager::readAF(string filename)
{
	VectorPointer res = VectorPointer(new Vector);
	read(filename, *res);
	return res;
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
	vector<double> massesFull; //create mass_per_atom*3 vector

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
//ADD sorting
		massIds = vector<int>(N);
		massesFull = vector<double>(3*N); //create mass_per_atom*3 vector
		if (line.find("Atoms", 0) != string::npos)
		{
			getline(fileInput, line);

			int mid=0;
			int aid=0; //atom id (for sort)
			for (int i =0; i < N; ++i)
			{
				getline(fileInput, line);
				std::istringstream iss(line);

				std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
						std::istream_iterator<std::string>());

				iss =  std::istringstream(results[2]);
				iss>>mid;
				mid = mid - 1;
				iss =  std::istringstream(results[0]);
				iss>>aid;
				aid = aid-1;//since lammps counts starting from 1
				massIds[aid] = mid ;

				//Dimensionality == 3
				double minvsqrt = 1.0 / sqrt(masses[mid]);
				massesFull[aid*3 + 0] = minvsqrt;
				massesFull[aid*3 + 1] = minvsqrt;
				massesFull[aid*3 + 2] = minvsqrt;
				if(aid >= N)
					processStatus(string("ERROR: FileManager::readLAMMPSData: aid >= N: ") +to_string(aid)+string(" ")+to_string(N));
				if(mid >= nM)
					processStatus(string("ERROR: FileManager::readLAMMPSData: mid >= nM: ") +to_string(mid)+string(" ")+to_string(nM));
			}
			break;
		}
	}
	minvSqrt = Vector::Map(massesFull.data(), massesFull.size());
	processStatus("MASS: mtypes:" + std::to_string(nM) + " " + std::to_string(N));
	Vol = Lx* Ly*Lz;
	if (Vol == 0.0f)
	{
		std::cout<<"Warning: Can't read box size from lammps data file (or it is zero, or it is 2d simulation)"<<std::endl;
	}
	fileInput.close();

	processStatus(string("FileManager::readLAMMPSData..finished  mem: ") + mem() );
	return Vol/N;
}

sMatrixPointer FileManager::readCSR(string fdata, string findices, string findptr)
{
	processStatus(string("Reading indptr.. mem: ") +  mem());

	FILE *stream;
	stream = fopen(findptr.c_str(), "r");
	if (stream == NULL)
	{
		std::cerr<<("Error opening CSR.inptr file: "+findptr +"\n");
		return nullptr;
	}
	FILE *stream3;
	stream3 = fopen(fdata.c_str(), "r");
	if (stream3 == NULL)
	{
		fclose(stream);
		std::cerr<<("Error opening CSR.data file\n");
		return nullptr;
	}
	FILE *stream2;
	stream2 = fopen(findices.c_str(), "r");

	if (stream2 == NULL)
	{
		fclose(stream);
		fclose(stream3);
		std::cerr<<("Error opening CSR.indices file\n");
		return nullptr;
	}

	vector<long int> indptr;
	long int val;
	while(fscanf(stream, "%ld", &val) != EOF)
	{
		indptr.push_back(val);
	}
	fclose(stream);
	unsigned int N=indptr.size()-1;


	//Read data and column indices
	long int nNon0 = *(indptr.end()-1); //number of non zero elements

	double dataval=0.0;
	long int indval=0;
	int rowLen = 0;

	//Create sparse matrix
	processStatus("Creating sparse matrix...");
	auto hessian = sMatrixPointer(new sMatrix(N,N));
	hessian->reserve( nNon0 + N);

	long int nel=0;
	processStatus("Reading Hessian from csr....");
	for (unsigned int i =0; i < N ;++i)
	{
		rowLen = indptr[i+1] - indptr[i];

		hessian->startVec(i);
		bool diag_zero = true;

		if(rowLen == 0)
			hessian->insertBack( i, i ) =  0.00f ;
		for (int j =0;j <rowLen;++j)
		{

			if (fscanf(stream3, "%lf", &dataval) != 1 || fscanf(stream2, "%ld", &indval) != 1)
			{
				fclose(stream2);
				fclose(stream3);
				return nullptr;
			}

			if(i == indval-1)
				diag_zero = false;
			if(indval-1>i && diag_zero)
			{
				hessian->insertBack( i, i ) =  0.00f ;
				nel++;
				diag_zero = false;
			}
			hessian->insertBack( i, indval-1) =  dataval ;
			nel++;
		}
		double p = double(nel)/nNon0;

		processRunningStatus(p);

	}
	processEnded();
	hessian->finalize();
	processStatus(string("Reading csr matrix finished... mem: ") + mem());
	fclose(stream2);
	fclose(stream3);

	return hessian;

}

sMatrixPointer FileManager::readCSR(string fdata, string findices, string findptr,
									sMatrixPointer hessian, vector<int>& sizes, vector<int>& displacements, MPI_Comm inworld)
{
	int m_mpi_rank,m_mpi_size;
	MPI_Comm_rank(inworld, &m_mpi_rank);
	MPI_Comm_size(inworld, &m_mpi_size);


	//ALL RANKS doing the same
	//------------------------------------------------------------------------------------------------------

	//Read indptr from CSR matrix (== cumulative number of nonzero elements in a row)
	processStatus(string("Reading indptr.. mem: ") +  mem());

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

	unsigned int nrows_per_rank = m_mpi_rank==(m_mpi_size-1)?N/m_mpi_size+N%m_mpi_size:N/m_mpi_size;
	int shift = N/m_mpi_size*m_mpi_rank; //dont need it
	MPI_Allgather( &nrows_per_rank, 1, MPI_INT, sizes.data(),         1, MPI_INT, inworld);
	MPI_Allgather( &shift,          1, MPI_INT, displacements.data(), 1, MPI_INT,  inworld);
	//+1 ensures that next inptr starts with last value of previous
	vector<long int>  indptr_per_rank(indptr.begin() + shift, indptr.begin() + shift + nrows_per_rank + 1);
	long int indptr_shift = indptr_per_rank[0];
	for(long int& e: indptr_per_rank) e-=indptr_shift;
	Vector v_indptr;// = zeros(indptr.size());

	//Read data and column indices
	//------------------------------------------------------------------------------------------------------

	long int nNon0 = *(indptr_per_rank.end()-1); //number of non zero elements

	FILE *stream3;
	stream3 = fopen(fdata.c_str(), "r");
	FILE *stream2;
	stream2 = fopen(findices.c_str(), "r");


	double dataval=0.0;
	long int indval=0;
	int rowLen = 0;

	//Create sparse matrix
	processStatus("Creating sparse matrix...");
	hessian = sMatrixPointer(new sMatrix(nrows_per_rank,N));

	//allocate space for all nonzero element + additional N,
	//in case any diag element is zero
	hessian->reserve( nNon0 + nrows_per_rank);

	long int nel=0;
	processStatus("Reading Hessian from csr....");
	//Skip to correct block of data/indices
	//------------------------------------------------------------------------------------------------------
	for(int k = 0; k < indptr_shift; ++k)
	{
		if (fscanf(stream3, "%lf", &dataval) != 1 || fscanf(stream2, "%ld", &indval) != 1)
		{
			fclose(stream2);
			fclose(stream3);
			return nullptr;
		}
	}
	//------------------------------------------------------------------------------------------------------
	unsigned int out=0;
	for (unsigned int i =0; i < nrows_per_rank ;++i)
	{
		rowLen = indptr_per_rank[i+1] - indptr_per_rank[i];

		hessian->startVec(i);
		bool diag_zero = true;

		if(rowLen == 0)
			hessian->insertBack( i, i ) =  0.00f ;
		for (int j =0;j <rowLen;++j)
		{
			if (fscanf(stream3, "%lf", &dataval) != 1 || fscanf(stream2, "%ld", &indval) != 1)
			{
				fclose(stream2);
				fclose(stream3);
				return nullptr;
			}
			if(i == indval-1)
				diag_zero = false;
			if(indval-1>i && diag_zero)
			{
				hessian->insertBack( i, i ) =  0.00f ;
				nel++;
				diag_zero = false;
			}
			hessian->insertBack( i, indval-1) =  dataval ;
			nel++;
		}
		double p = double(nel)/nNon0;
		if (100 * p > out )
		{
			processRunningStatus(p);
			out+=10;
		}

	}
	processEnded();
	fclose(stream2);
	fclose(stream3);
	hessian->finalize();
	processStatus(string("Reading csr matrix finished... mem: ") + mem());

	return hessian;
}
KPMGParams FileManager::readKPMGParameters(string filename)
{
	std::unordered_map<std::string, std::vector<std::string>> params = readParameters(filename);
	if( params.empty() )
	{
		processStatus("WARNING: readKPMGParameters: Please provide parameters file, using default atom values");
		return KPMGParams();
//		exit(EXIT_FAILURE);
	}
//	GA{GAT}, nu{nuT}, wmin{wminT}, wmax{wmaxT}, nw{nPoints}, c_wcut,nFreq
	KPMGParams kpmGParams;
	if (params.count("GA"))
	{
		kpmGParams.GA = std::stof(params.at("GA")[0]);
	}
	if (params.count("nu"))
	{
		kpmGParams.nu = std::stof(params.at("nu")[0]);
	}
	if (params.count("wmin"))
	{
		kpmGParams.wmin = std::stof(params.at("wmin")[0]);
	}

	if (params.count("wmax"))
	{
		kpmGParams.wmax = std::stof(params.at("wmax")[0]);
	}

	if (params.count("wcount"))
	{
		kpmGParams.wcount = std::stoi(params.at("wcount")[0]);
	}

	if (params.count("wcut"))
	{
		kpmGParams.wcut = std::stof(params.at("wcut")[0]);
	}

	if (params.count("nFreq"))
	{
		kpmGParams.nFreq = std::stoi(params.at("nFreq")[0]);
	}

	return kpmGParams;
}

std::unordered_map<std::string, std::vector<std::string>> FileManager::readParameters(string filename)
{
	ifstream ifs{filename};
	if (!ifs)
	{
		processStatus("ERROR: cannot open file");
		return std::unordered_map<std::string, std::vector<std::string>>{};
	}
	std::string line;
	std::unordered_map<std::string, std::vector<std::string>> properties;

	while(std::getline(ifs, line))
	{
		std::istringstream is_line(line);
		std::string key;
		is_line >> key;
		cout << key << ": ";
		std::string word;
		std::vector<std::string> vals;
		while (is_line >> word)
		{
			// print the read word
			cout << word << " ";
			vals.push_back(word);
		}
		cout <<  "\n";
		properties.emplace(key, vals);
	}
	return properties;
}
