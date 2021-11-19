/*
 * FileManager.h
 *
 *  Created on: Aug 4, 2020
 *      Author: ivan
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <stdio.h>
#include <iostream>
#include "core.h"
#include <unistd.h>
std::string mem();
using namespace std;

class FileManager {
public:
	FileManager();
	virtual ~FileManager();

	//Read-write methods. Must be separated.
	//-----------------------------------------
	/**
	 * @brief Reads the CSR-matrix from 3 files: fdata, findptr, findptr
	 * @param[in] fdata    Filename of the data of the CSR-matrix.
	 * @param[in] findices Filename of the indices of the CSR-matrix. "indices" shows the column index of all non zero elements.
	 * @param[in] findptr  Filename of the indptr of the CSR-matrix. "indptr" shows the cumulative number of non zero elements in each row.,
	 * @param[out] hessian Sparse matrix (hessian)
	 */

	void readCSR(string fdata, string findices, string findptr, sMatrix& hessian, vector<int>& sizes, vector<int>& displacements, MPI_Comm inworld=MPI_COMM_WORLD);
	void readCSR(string fdata, string findices, string findptr, sMatrix& hessian);
	void write(string filename, const Vector& v1, const Vector& v2);
	void write(string filename, const Vector& v1);

	void read(string filename, Vector& v1);
	/**
	 * @brief Reads the affine forcefield vector from file. (Needed for GammaDOS and G'(G'') calculations. Not needed for VDOS only.)
	 * @param[in] filename  Filename of the affine force field vector.
	 * @param[in] af  The affine force field vector.
	 */
	void readAF(string filename, Vector& af);
	/**
	 * @brief Reads mass info from Lammps data file. Fills 1/sqrt(m_i) vector. Returns box Volume
	 */
	float readLAMMPSData(string filename, Vector& minvSqrt); //reads m_M (particle masses) from lammps data file

	//-----------------------------------------
};

#endif /* FILEMANAGER_H_ */
