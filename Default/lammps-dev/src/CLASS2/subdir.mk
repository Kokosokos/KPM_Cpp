################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/CLASS2/angle_class2.cpp \
../lammps-dev/src/CLASS2/bond_class2.cpp \
../lammps-dev/src/CLASS2/dihedral_class2.cpp \
../lammps-dev/src/CLASS2/improper_class2.cpp \
../lammps-dev/src/CLASS2/pair_lj_class2.cpp \
../lammps-dev/src/CLASS2/pair_lj_class2_coul_cut.cpp \
../lammps-dev/src/CLASS2/pair_lj_class2_coul_long.cpp 

OBJS += \
./lammps-dev/src/CLASS2/angle_class2.o \
./lammps-dev/src/CLASS2/bond_class2.o \
./lammps-dev/src/CLASS2/dihedral_class2.o \
./lammps-dev/src/CLASS2/improper_class2.o \
./lammps-dev/src/CLASS2/pair_lj_class2.o \
./lammps-dev/src/CLASS2/pair_lj_class2_coul_cut.o \
./lammps-dev/src/CLASS2/pair_lj_class2_coul_long.o 

CPP_DEPS += \
./lammps-dev/src/CLASS2/angle_class2.d \
./lammps-dev/src/CLASS2/bond_class2.d \
./lammps-dev/src/CLASS2/dihedral_class2.d \
./lammps-dev/src/CLASS2/improper_class2.d \
./lammps-dev/src/CLASS2/pair_lj_class2.d \
./lammps-dev/src/CLASS2/pair_lj_class2_coul_cut.d \
./lammps-dev/src/CLASS2/pair_lj_class2_coul_long.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/CLASS2/%.o: ../lammps-dev/src/CLASS2/%.cpp lammps-dev/src/CLASS2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


