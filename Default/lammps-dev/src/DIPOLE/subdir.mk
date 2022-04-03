################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/DIPOLE/atom_vec_dipole.cpp \
../lammps-dev/src/DIPOLE/pair_lj_cut_dipole_cut.cpp \
../lammps-dev/src/DIPOLE/pair_lj_cut_dipole_long.cpp \
../lammps-dev/src/DIPOLE/pair_lj_long_dipole_long.cpp 

OBJS += \
./lammps-dev/src/DIPOLE/atom_vec_dipole.o \
./lammps-dev/src/DIPOLE/pair_lj_cut_dipole_cut.o \
./lammps-dev/src/DIPOLE/pair_lj_cut_dipole_long.o \
./lammps-dev/src/DIPOLE/pair_lj_long_dipole_long.o 

CPP_DEPS += \
./lammps-dev/src/DIPOLE/atom_vec_dipole.d \
./lammps-dev/src/DIPOLE/pair_lj_cut_dipole_cut.d \
./lammps-dev/src/DIPOLE/pair_lj_cut_dipole_long.d \
./lammps-dev/src/DIPOLE/pair_lj_long_dipole_long.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/DIPOLE/%.o: ../lammps-dev/src/DIPOLE/%.cpp lammps-dev/src/DIPOLE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


