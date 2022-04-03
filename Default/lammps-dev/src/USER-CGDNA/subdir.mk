################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-CGDNA/bond_oxdna2_fene.cpp \
../lammps-dev/src/USER-CGDNA/bond_oxdna_fene.cpp \
../lammps-dev/src/USER-CGDNA/bond_oxrna2_fene.cpp \
../lammps-dev/src/USER-CGDNA/fix_nve_dot.cpp \
../lammps-dev/src/USER-CGDNA/fix_nve_dotc_langevin.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna2_coaxstk.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna2_dh.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna2_excv.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna_coaxstk.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna_excv.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna_hbond.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna_stk.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxdna_xstk.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxrna2_dh.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxrna2_excv.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxrna2_hbond.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxrna2_stk.cpp \
../lammps-dev/src/USER-CGDNA/pair_oxrna2_xstk.cpp 

OBJS += \
./lammps-dev/src/USER-CGDNA/bond_oxdna2_fene.o \
./lammps-dev/src/USER-CGDNA/bond_oxdna_fene.o \
./lammps-dev/src/USER-CGDNA/bond_oxrna2_fene.o \
./lammps-dev/src/USER-CGDNA/fix_nve_dot.o \
./lammps-dev/src/USER-CGDNA/fix_nve_dotc_langevin.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna2_coaxstk.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna2_dh.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna2_excv.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna_coaxstk.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna_excv.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna_hbond.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna_stk.o \
./lammps-dev/src/USER-CGDNA/pair_oxdna_xstk.o \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_dh.o \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_excv.o \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_hbond.o \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_stk.o \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_xstk.o 

CPP_DEPS += \
./lammps-dev/src/USER-CGDNA/bond_oxdna2_fene.d \
./lammps-dev/src/USER-CGDNA/bond_oxdna_fene.d \
./lammps-dev/src/USER-CGDNA/bond_oxrna2_fene.d \
./lammps-dev/src/USER-CGDNA/fix_nve_dot.d \
./lammps-dev/src/USER-CGDNA/fix_nve_dotc_langevin.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna2_coaxstk.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna2_dh.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna2_excv.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna_coaxstk.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna_excv.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna_hbond.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna_stk.d \
./lammps-dev/src/USER-CGDNA/pair_oxdna_xstk.d \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_dh.d \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_excv.d \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_hbond.d \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_stk.d \
./lammps-dev/src/USER-CGDNA/pair_oxrna2_xstk.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-CGDNA/%.o: ../lammps-dev/src/USER-CGDNA/%.cpp lammps-dev/src/USER-CGDNA/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


