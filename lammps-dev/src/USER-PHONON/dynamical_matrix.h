//
// Created by charlie sievers on 6/21/18.
//

#ifdef COMMAND_CLASS

CommandStyle(dynamical_matrix,DynamicalMatrix)

#else

#ifndef LMP_DYNAMICAL_MATRIX_H
#define LMP_DYNAMICAL_MATRIX_H

#include "pointers.h"

//class A;
//typedef sMatrix A;

namespace LAMMPS_NS {

    class DynamicalMatrix : protected Pointers {
    public:
        DynamicalMatrix(class LAMMPS *);
        virtual ~DynamicalMatrix();
        void command(int, char **);
        void setup();

    protected:
        int eflag,vflag;            // flags for energy/virial computation
        int external_force_clear;   // clear forces locally or externally


        int triclinic;              // 0 if domain is orthog, 1 if triclinic
        int pairflag;

        int pair_compute_flag;            // 0 if pair->compute is skipped
        int kspace_compute_flag;          // 0 if kspace->compute is skipped

        int nvec;                   // local atomic dof = length of xvec

        void update_force();
        void force_clear();
        virtual void openfile(const char* filename);
        void openCSR();
        virtual void closefile();
    private:
        void options(int, char **);
        void kpmOptions(int, char **);
        void calculateMatrix();
        void dynmat_clear(double **dynmat);
        void create_groupmap();
        void writeMatrix(double **dynmat);
		void writeMatrixCSR(double **dynmat, int ni);
		void writeMatrixSparse(double **dynmat, int ni);
        void convert_units(const char *style);
        void displace_atom(int local_idx, int direction, int magnitude);

        double conversion;
        double conv_energy;
        double conv_distance;
        double conv_mass;
        double del;
        int igroup,groupbit;
        bigint gcount;             // number of atoms in group
        bigint dynlen;             // rank of dynamical matrix
        int scaleflag;
        int me;
        bigint *groupmap;

        int compressed;            // 1 if dump file is written compressed, 0 no
        int binaryflag;            // 1 if dump file is written binary, 0 no
		int sparseflag;				// 0 if u want to use dense matrix output, 1 - for python sparse matrix
		int csrflag;

        int file_opened;           // 1 if openfile method has been called, 0 no
        int file_flag;             // 1 custom file name, 0 dynmat.dat

        int kpm_dos_flag;
        FILE *fp;

			
        FILE *fp_data;
        FILE *fp_indptr;
        FILE *fp_indices;
		bigint m_indptr;
		float m_hcut;
    };
}


#endif //LMP_DYNAMICAL_MATRIX_H
#endif
