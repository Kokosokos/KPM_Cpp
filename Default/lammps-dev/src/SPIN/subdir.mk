################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/SPIN/atom_vec_spin.cpp \
../lammps-dev/src/SPIN/compute_spin.cpp \
../lammps-dev/src/SPIN/fix_langevin_spin.cpp \
../lammps-dev/src/SPIN/fix_neb_spin.cpp \
../lammps-dev/src/SPIN/fix_nve_spin.cpp \
../lammps-dev/src/SPIN/fix_precession_spin.cpp \
../lammps-dev/src/SPIN/fix_setforce_spin.cpp \
../lammps-dev/src/SPIN/min_spin.cpp \
../lammps-dev/src/SPIN/min_spin_cg.cpp \
../lammps-dev/src/SPIN/min_spin_lbfgs.cpp \
../lammps-dev/src/SPIN/neb_spin.cpp \
../lammps-dev/src/SPIN/pair_spin.cpp \
../lammps-dev/src/SPIN/pair_spin_dipole_cut.cpp \
../lammps-dev/src/SPIN/pair_spin_dipole_long.cpp \
../lammps-dev/src/SPIN/pair_spin_dmi.cpp \
../lammps-dev/src/SPIN/pair_spin_exchange.cpp \
../lammps-dev/src/SPIN/pair_spin_exchange_biquadratic.cpp \
../lammps-dev/src/SPIN/pair_spin_magelec.cpp \
../lammps-dev/src/SPIN/pair_spin_neel.cpp 

OBJS += \
./lammps-dev/src/SPIN/atom_vec_spin.o \
./lammps-dev/src/SPIN/compute_spin.o \
./lammps-dev/src/SPIN/fix_langevin_spin.o \
./lammps-dev/src/SPIN/fix_neb_spin.o \
./lammps-dev/src/SPIN/fix_nve_spin.o \
./lammps-dev/src/SPIN/fix_precession_spin.o \
./lammps-dev/src/SPIN/fix_setforce_spin.o \
./lammps-dev/src/SPIN/min_spin.o \
./lammps-dev/src/SPIN/min_spin_cg.o \
./lammps-dev/src/SPIN/min_spin_lbfgs.o \
./lammps-dev/src/SPIN/neb_spin.o \
./lammps-dev/src/SPIN/pair_spin.o \
./lammps-dev/src/SPIN/pair_spin_dipole_cut.o \
./lammps-dev/src/SPIN/pair_spin_dipole_long.o \
./lammps-dev/src/SPIN/pair_spin_dmi.o \
./lammps-dev/src/SPIN/pair_spin_exchange.o \
./lammps-dev/src/SPIN/pair_spin_exchange_biquadratic.o \
./lammps-dev/src/SPIN/pair_spin_magelec.o \
./lammps-dev/src/SPIN/pair_spin_neel.o 

CPP_DEPS += \
./lammps-dev/src/SPIN/atom_vec_spin.d \
./lammps-dev/src/SPIN/compute_spin.d \
./lammps-dev/src/SPIN/fix_langevin_spin.d \
./lammps-dev/src/SPIN/fix_neb_spin.d \
./lammps-dev/src/SPIN/fix_nve_spin.d \
./lammps-dev/src/SPIN/fix_precession_spin.d \
./lammps-dev/src/SPIN/fix_setforce_spin.d \
./lammps-dev/src/SPIN/min_spin.d \
./lammps-dev/src/SPIN/min_spin_cg.d \
./lammps-dev/src/SPIN/min_spin_lbfgs.d \
./lammps-dev/src/SPIN/neb_spin.d \
./lammps-dev/src/SPIN/pair_spin.d \
./lammps-dev/src/SPIN/pair_spin_dipole_cut.d \
./lammps-dev/src/SPIN/pair_spin_dipole_long.d \
./lammps-dev/src/SPIN/pair_spin_dmi.d \
./lammps-dev/src/SPIN/pair_spin_exchange.d \
./lammps-dev/src/SPIN/pair_spin_exchange_biquadratic.d \
./lammps-dev/src/SPIN/pair_spin_magelec.d \
./lammps-dev/src/SPIN/pair_spin_neel.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/SPIN/%.o: ../lammps-dev/src/SPIN/%.cpp lammps-dev/src/SPIN/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


