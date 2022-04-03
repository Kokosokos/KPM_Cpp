################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/CORESHELL/compute_temp_cs.cpp \
../lammps-dev/src/CORESHELL/pair_born_coul_dsf_cs.cpp \
../lammps-dev/src/CORESHELL/pair_born_coul_long_cs.cpp \
../lammps-dev/src/CORESHELL/pair_born_coul_wolf_cs.cpp \
../lammps-dev/src/CORESHELL/pair_buck_coul_long_cs.cpp \
../lammps-dev/src/CORESHELL/pair_coul_long_cs.cpp \
../lammps-dev/src/CORESHELL/pair_coul_wolf_cs.cpp \
../lammps-dev/src/CORESHELL/pair_lj_class2_coul_long_cs.cpp \
../lammps-dev/src/CORESHELL/pair_lj_cut_coul_long_cs.cpp 

OBJS += \
./lammps-dev/src/CORESHELL/compute_temp_cs.o \
./lammps-dev/src/CORESHELL/pair_born_coul_dsf_cs.o \
./lammps-dev/src/CORESHELL/pair_born_coul_long_cs.o \
./lammps-dev/src/CORESHELL/pair_born_coul_wolf_cs.o \
./lammps-dev/src/CORESHELL/pair_buck_coul_long_cs.o \
./lammps-dev/src/CORESHELL/pair_coul_long_cs.o \
./lammps-dev/src/CORESHELL/pair_coul_wolf_cs.o \
./lammps-dev/src/CORESHELL/pair_lj_class2_coul_long_cs.o \
./lammps-dev/src/CORESHELL/pair_lj_cut_coul_long_cs.o 

CPP_DEPS += \
./lammps-dev/src/CORESHELL/compute_temp_cs.d \
./lammps-dev/src/CORESHELL/pair_born_coul_dsf_cs.d \
./lammps-dev/src/CORESHELL/pair_born_coul_long_cs.d \
./lammps-dev/src/CORESHELL/pair_born_coul_wolf_cs.d \
./lammps-dev/src/CORESHELL/pair_buck_coul_long_cs.d \
./lammps-dev/src/CORESHELL/pair_coul_long_cs.d \
./lammps-dev/src/CORESHELL/pair_coul_wolf_cs.d \
./lammps-dev/src/CORESHELL/pair_lj_class2_coul_long_cs.d \
./lammps-dev/src/CORESHELL/pair_lj_cut_coul_long_cs.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/CORESHELL/%.o: ../lammps-dev/src/CORESHELL/%.cpp lammps-dev/src/CORESHELL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


