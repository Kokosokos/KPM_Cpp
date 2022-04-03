################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/PERI/atom_vec_peri.cpp \
../lammps-dev/src/PERI/compute_damage_atom.cpp \
../lammps-dev/src/PERI/compute_dilatation_atom.cpp \
../lammps-dev/src/PERI/compute_plasticity_atom.cpp \
../lammps-dev/src/PERI/fix_peri_neigh.cpp \
../lammps-dev/src/PERI/pair_peri_eps.cpp \
../lammps-dev/src/PERI/pair_peri_lps.cpp \
../lammps-dev/src/PERI/pair_peri_pmb.cpp \
../lammps-dev/src/PERI/pair_peri_ves.cpp 

OBJS += \
./lammps-dev/src/PERI/atom_vec_peri.o \
./lammps-dev/src/PERI/compute_damage_atom.o \
./lammps-dev/src/PERI/compute_dilatation_atom.o \
./lammps-dev/src/PERI/compute_plasticity_atom.o \
./lammps-dev/src/PERI/fix_peri_neigh.o \
./lammps-dev/src/PERI/pair_peri_eps.o \
./lammps-dev/src/PERI/pair_peri_lps.o \
./lammps-dev/src/PERI/pair_peri_pmb.o \
./lammps-dev/src/PERI/pair_peri_ves.o 

CPP_DEPS += \
./lammps-dev/src/PERI/atom_vec_peri.d \
./lammps-dev/src/PERI/compute_damage_atom.d \
./lammps-dev/src/PERI/compute_dilatation_atom.d \
./lammps-dev/src/PERI/compute_plasticity_atom.d \
./lammps-dev/src/PERI/fix_peri_neigh.d \
./lammps-dev/src/PERI/pair_peri_eps.d \
./lammps-dev/src/PERI/pair_peri_lps.d \
./lammps-dev/src/PERI/pair_peri_pmb.d \
./lammps-dev/src/PERI/pair_peri_ves.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/PERI/%.o: ../lammps-dev/src/PERI/%.cpp lammps-dev/src/PERI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


