################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-SPH/atom_vec_meso.cpp \
../lammps-dev/src/USER-SPH/atom_vec_sph.cpp \
../lammps-dev/src/USER-SPH/compute_meso_e_atom.cpp \
../lammps-dev/src/USER-SPH/compute_meso_rho_atom.cpp \
../lammps-dev/src/USER-SPH/compute_meso_t_atom.cpp \
../lammps-dev/src/USER-SPH/compute_sph_e_atom.cpp \
../lammps-dev/src/USER-SPH/compute_sph_rho_atom.cpp \
../lammps-dev/src/USER-SPH/compute_sph_t_atom.cpp \
../lammps-dev/src/USER-SPH/fix_meso.cpp \
../lammps-dev/src/USER-SPH/fix_meso_stationary.cpp \
../lammps-dev/src/USER-SPH/fix_sph.cpp \
../lammps-dev/src/USER-SPH/fix_sph_stationary.cpp \
../lammps-dev/src/USER-SPH/pair_sph_heatconduction.cpp \
../lammps-dev/src/USER-SPH/pair_sph_idealgas.cpp \
../lammps-dev/src/USER-SPH/pair_sph_lj.cpp \
../lammps-dev/src/USER-SPH/pair_sph_rhosum.cpp \
../lammps-dev/src/USER-SPH/pair_sph_taitwater.cpp \
../lammps-dev/src/USER-SPH/pair_sph_taitwater_morris.cpp 

OBJS += \
./lammps-dev/src/USER-SPH/atom_vec_meso.o \
./lammps-dev/src/USER-SPH/atom_vec_sph.o \
./lammps-dev/src/USER-SPH/compute_meso_e_atom.o \
./lammps-dev/src/USER-SPH/compute_meso_rho_atom.o \
./lammps-dev/src/USER-SPH/compute_meso_t_atom.o \
./lammps-dev/src/USER-SPH/compute_sph_e_atom.o \
./lammps-dev/src/USER-SPH/compute_sph_rho_atom.o \
./lammps-dev/src/USER-SPH/compute_sph_t_atom.o \
./lammps-dev/src/USER-SPH/fix_meso.o \
./lammps-dev/src/USER-SPH/fix_meso_stationary.o \
./lammps-dev/src/USER-SPH/fix_sph.o \
./lammps-dev/src/USER-SPH/fix_sph_stationary.o \
./lammps-dev/src/USER-SPH/pair_sph_heatconduction.o \
./lammps-dev/src/USER-SPH/pair_sph_idealgas.o \
./lammps-dev/src/USER-SPH/pair_sph_lj.o \
./lammps-dev/src/USER-SPH/pair_sph_rhosum.o \
./lammps-dev/src/USER-SPH/pair_sph_taitwater.o \
./lammps-dev/src/USER-SPH/pair_sph_taitwater_morris.o 

CPP_DEPS += \
./lammps-dev/src/USER-SPH/atom_vec_meso.d \
./lammps-dev/src/USER-SPH/atom_vec_sph.d \
./lammps-dev/src/USER-SPH/compute_meso_e_atom.d \
./lammps-dev/src/USER-SPH/compute_meso_rho_atom.d \
./lammps-dev/src/USER-SPH/compute_meso_t_atom.d \
./lammps-dev/src/USER-SPH/compute_sph_e_atom.d \
./lammps-dev/src/USER-SPH/compute_sph_rho_atom.d \
./lammps-dev/src/USER-SPH/compute_sph_t_atom.d \
./lammps-dev/src/USER-SPH/fix_meso.d \
./lammps-dev/src/USER-SPH/fix_meso_stationary.d \
./lammps-dev/src/USER-SPH/fix_sph.d \
./lammps-dev/src/USER-SPH/fix_sph_stationary.d \
./lammps-dev/src/USER-SPH/pair_sph_heatconduction.d \
./lammps-dev/src/USER-SPH/pair_sph_idealgas.d \
./lammps-dev/src/USER-SPH/pair_sph_lj.d \
./lammps-dev/src/USER-SPH/pair_sph_rhosum.d \
./lammps-dev/src/USER-SPH/pair_sph_taitwater.d \
./lammps-dev/src/USER-SPH/pair_sph_taitwater_morris.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-SPH/%.o: ../lammps-dev/src/USER-SPH/%.cpp lammps-dev/src/USER-SPH/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


