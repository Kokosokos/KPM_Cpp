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

using namespace std;


#include <Eigen/Core>
#include <Eigen/SparseCore>




int main(int argc, char *argv[]) {

	MPI::Init(argc, argv);
	int rank = MPI::COMM_WORLD.Get_rank();
	//	Eigen::setNbThreads(4);
	clock_t t;
	t = clock();

	int K = 1000;
	int R = 20;
	KPM kpm( K, R );
	kpm.m_emin = -10.5022;
	kpm.m_emax = 4367.96;
	//	if(rank == 0)
	//	{
	//	kpm.findEmin();
	//	kpm.findEmax();
	kpm.readLAMMPSData("test/a_data.file");

	kpm.HTilde();
	kpm.readAF("test/dF.csv");

	//	std::cout<<kpm.m_af<<std::endl;
	//	}

//	Vector gp = kpm.getCoeffDOS();
	kpm.setR(1000);
	Vector gp2 = kpm.getCoeffGammaDOS();
	if(rank == 0)
	{
		Vector freq = arange(400, sgn(kpm.m_emin)*sqrt(fabs(kpm.m_emin)), sqrt(kpm.m_emax));
//		Vector dos = kpm.sumSeries(freq, gp);
		Vector gammaDos = kpm.sumSeries(freq, gp2);
//		kpm.write("gP.dat",gp);
//		kpm.write("DOS.dat",freq, dos);

		kpm.write("gPgamma.dat",gp2);
		kpm.write("gammaDOS.dat",freq, gammaDos);
		t = clock() - t;

		printf ("It took me %d clicks (%f seconds).\n",(int) t,((float)t)/CLOCKS_PER_SEC);
		FILE *stream;
		stream = fopen("time.dat", "a");
		fprintf(stream, "%d %d %d %f\n", K, R, (int) t, ((float)t)/CLOCKS_PER_SEC);
	}



	MPI::Finalize();
	return 0;
}
