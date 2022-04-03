################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-FEP/compute_fep.cpp \
../lammps-dev/src/USER-FEP/fix_adapt_fep.cpp \
../lammps-dev/src/USER-FEP/pair_coul_cut_soft.cpp \
../lammps-dev/src/USER-FEP/pair_coul_long_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_charmm_coul_long_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_class2_coul_cut_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_class2_coul_long_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_class2_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_cut_coul_cut_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_cut_coul_long_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_cut_soft.cpp \
../lammps-dev/src/USER-FEP/pair_lj_cut_tip4p_long_soft.cpp \
../lammps-dev/src/USER-FEP/pair_morse_soft.cpp \
../lammps-dev/src/USER-FEP/pair_tip4p_long_soft.cpp 

OBJS += \
./lammps-dev/src/USER-FEP/compute_fep.o \
./lammps-dev/src/USER-FEP/fix_adapt_fep.o \
./lammps-dev/src/USER-FEP/pair_coul_cut_soft.o \
./lammps-dev/src/USER-FEP/pair_coul_long_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_charmm_coul_long_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_class2_coul_cut_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_class2_coul_long_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_class2_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_cut_coul_cut_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_cut_coul_long_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_cut_soft.o \
./lammps-dev/src/USER-FEP/pair_lj_cut_tip4p_long_soft.o \
./lammps-dev/src/USER-FEP/pair_morse_soft.o \
./lammps-dev/src/USER-FEP/pair_tip4p_long_soft.o 

CPP_DEPS += \
./lammps-dev/src/USER-FEP/compute_fep.d \
./lammps-dev/src/USER-FEP/fix_adapt_fep.d \
./lammps-dev/src/USER-FEP/pair_coul_cut_soft.d \
./lammps-dev/src/USER-FEP/pair_coul_long_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_charmm_coul_long_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_class2_coul_cut_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_class2_coul_long_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_class2_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_cut_coul_cut_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_cut_coul_long_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_cut_soft.d \
./lammps-dev/src/USER-FEP/pair_lj_cut_tip4p_long_soft.d \
./lammps-dev/src/USER-FEP/pair_morse_soft.d \
./lammps-dev/src/USER-FEP/pair_tip4p_long_soft.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-FEP/%.o: ../lammps-dev/src/USER-FEP/%.cpp lammps-dev/src/USER-FEP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


