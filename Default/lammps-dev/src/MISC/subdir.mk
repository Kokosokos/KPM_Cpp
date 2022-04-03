################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/MISC/compute_msd_nongauss.cpp \
../lammps-dev/src/MISC/compute_ti.cpp \
../lammps-dev/src/MISC/dump_xtc.cpp \
../lammps-dev/src/MISC/fix_deposit.cpp \
../lammps-dev/src/MISC/fix_efield.cpp \
../lammps-dev/src/MISC/fix_evaporate.cpp \
../lammps-dev/src/MISC/fix_gld.cpp \
../lammps-dev/src/MISC/fix_oneway.cpp \
../lammps-dev/src/MISC/fix_orient_bcc.cpp \
../lammps-dev/src/MISC/fix_orient_fcc.cpp \
../lammps-dev/src/MISC/fix_thermal_conductivity.cpp \
../lammps-dev/src/MISC/fix_ttm.cpp \
../lammps-dev/src/MISC/fix_viscosity.cpp \
../lammps-dev/src/MISC/pair_nm_cut.cpp \
../lammps-dev/src/MISC/pair_nm_cut_coul_cut.cpp \
../lammps-dev/src/MISC/pair_nm_cut_coul_long.cpp \
../lammps-dev/src/MISC/xdr_compat.cpp 

OBJS += \
./lammps-dev/src/MISC/compute_msd_nongauss.o \
./lammps-dev/src/MISC/compute_ti.o \
./lammps-dev/src/MISC/dump_xtc.o \
./lammps-dev/src/MISC/fix_deposit.o \
./lammps-dev/src/MISC/fix_efield.o \
./lammps-dev/src/MISC/fix_evaporate.o \
./lammps-dev/src/MISC/fix_gld.o \
./lammps-dev/src/MISC/fix_oneway.o \
./lammps-dev/src/MISC/fix_orient_bcc.o \
./lammps-dev/src/MISC/fix_orient_fcc.o \
./lammps-dev/src/MISC/fix_thermal_conductivity.o \
./lammps-dev/src/MISC/fix_ttm.o \
./lammps-dev/src/MISC/fix_viscosity.o \
./lammps-dev/src/MISC/pair_nm_cut.o \
./lammps-dev/src/MISC/pair_nm_cut_coul_cut.o \
./lammps-dev/src/MISC/pair_nm_cut_coul_long.o \
./lammps-dev/src/MISC/xdr_compat.o 

CPP_DEPS += \
./lammps-dev/src/MISC/compute_msd_nongauss.d \
./lammps-dev/src/MISC/compute_ti.d \
./lammps-dev/src/MISC/dump_xtc.d \
./lammps-dev/src/MISC/fix_deposit.d \
./lammps-dev/src/MISC/fix_efield.d \
./lammps-dev/src/MISC/fix_evaporate.d \
./lammps-dev/src/MISC/fix_gld.d \
./lammps-dev/src/MISC/fix_oneway.d \
./lammps-dev/src/MISC/fix_orient_bcc.d \
./lammps-dev/src/MISC/fix_orient_fcc.d \
./lammps-dev/src/MISC/fix_thermal_conductivity.d \
./lammps-dev/src/MISC/fix_ttm.d \
./lammps-dev/src/MISC/fix_viscosity.d \
./lammps-dev/src/MISC/pair_nm_cut.d \
./lammps-dev/src/MISC/pair_nm_cut_coul_cut.d \
./lammps-dev/src/MISC/pair_nm_cut_coul_long.d \
./lammps-dev/src/MISC/xdr_compat.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/MISC/%.o: ../lammps-dev/src/MISC/%.cpp lammps-dev/src/MISC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


