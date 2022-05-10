/*
 * KPMParameters.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: ivan
 */

#include "KPMParameters.h"

#include "FileManager.h"
#include <fstream>
int k = 0;
bool KPMParams::writeToFile(std::string filename)
{
	k+=1;
	ofstream ofs{filename};
	if (!ofs)
	{
		processStatus("ERROR: cannot open file");
		return false;
	}

	if (mode == KPMMode::DOS)
	{
		ofs << "MODE DOS  #DOS/GDOS\n";
	}
	else
	{
		ofs << "MODE GDOS #DOS/GDOS\n";
	}
	ofs << "K "<<K<<"\n";
	ofs << "R "<<R<<"\n";
	ofs << "epsilon "<<epsilon<<"\n";
	if (kernel == KPMKernels::Jackson)
		ofs << "kernel Jackson #Jackson/Lorentz\n";
	else
		ofs << "kernel Lorentz #Jackson/Lorentz\n";

	ofs << "Emin "<<emin<<"\n";
	ofs << "Emax "<<emax<<"\n";
	if (mode == KPMMode::GDOS)
	{
		ofs << "Lammps Data File "<<lammps_data_file<<"\n";
		ofs << "AF File "<<af_file<<"\n";
	}
	ofs.close();
	return true;
}
bool KPMParams::readFromFile(std::string filename)
{
	k+=1;
	ifstream ifs{filename};
	if (!ifs)
	{
		processStatus("ERROR: cannot open file");
		return false;
	}

	std::string temp;
	ifs>>temp; // == MODE
	ifs>>temp;
	if (temp == "DOS")
		mode = KPMMode::DOS;
	else if (temp == "GDOS")
		mode = KPMMode::GDOS;
	else
	{
		processStatus("No such mode:: please choose DOS or GDOS");
		return false;
	}
	ifs>>temp;

	ifs>>temp;
	ifs>>K;

	ifs>>temp;
	ifs>>R;
	ifs>>temp;
	ifs>>epsilon;

	ifs>>temp;
	ifs>>temp;
	if (temp == "Jackson")
		kernel = KPMKernels::Jackson;
	else if (temp == "Lorentz")
		kernel = KPMKernels::Lorentz;
	else
	{
		processStatus("No such kernel: please choose Jackson or Lorentz");
		return false;
	}
	ifs>>temp;
	setK(K);

	ifs>>temp;
	ifs>>emin;

	ifs>>temp;
	ifs>>emax;
	if (mode == KPMMode::GDOS)
	{
		ifs>>temp;
		ifs>>lammps_data_file;

		ifs>>temp;
		ifs>>af_file;

		processStatus("AF: "+af_file);
		processStatus("M: "+lammps_data_file);

		readM();
		readAF();
		processStatus("Config reading fnished");
	}
	ifs.close();
	return true;
}

bool KPMParams::readAF()
{
	FileManager fmanager;
	fmanager.readAF(af_file, af);
	af = MinvSqrt.cwiseProduct( af );
	fmanager.write("af.dat",af);
	return true;
}
bool KPMParams::readM()
{
	FileManager fmanager;
	density = fmanager.readLAMMPSData(lammps_data_file, MinvSqrt);
	return true;
}

void KPMParams::setMassVectorInvSqrt(float m, unsigned int DOF)
{
	MinvSqrt = 1.0 / sqrt(m) * ones(DOF);
//	m_MinvSqrt = Vector::Map(massesFull.data(), massesFull.size());
}
//-------------------------------------------------------------------------------

void KPMParams::setMassVectorInvSqrt( const Vector& mInvSqrt)
{
	MinvSqrt = mInvSqrt;
}
//-------------------------------------------------------------------------------

void KPMParams::setAF(const Vector& iaf)
{
	af = MinvSqrt.cwiseProduct( iaf );
}

void KPMParams::setK(unsigned int KK)
{
	K = KK;
	//Jackson kernel
	if(kernel == KPMKernels::Jackson)
		jacksonKernel(K);
	if(kernel == KPMKernels::Lorentz)
		lorentzKernel(K, lkernel);
}

void KPMParams::jacksonKernel(int K)
{
	Vector n = arange(K);
	m_jk = ((K+1)*ones(n.size())-n);

	m_jk = m_jk.cwiseProduct( cos((c_PI/(K+1))*n));
	m_jk += sin(c_PI*n/(K+1))/tan(c_PI/(K+1)) ;
	m_jk *= (1.0/(K+1));
}
void KPMParams::lorentzKernel(int K, int parameter )
{
	Vector n = arange(K);
	m_jk = sinh(parameter*(ones(n.size())-n/K))/sinh(parameter);
}
