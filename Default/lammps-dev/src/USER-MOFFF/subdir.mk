################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-MOFFF/angle_class2_p6.cpp \
../lammps-dev/src/USER-MOFFF/angle_cosine_buck6d.cpp \
../lammps-dev/src/USER-MOFFF/improper_inversion_harmonic.cpp \
../lammps-dev/src/USER-MOFFF/pair_buck6d_coul_gauss_dsf.cpp \
../lammps-dev/src/USER-MOFFF/pair_buck6d_coul_gauss_long.cpp 

OBJS += \
./lammps-dev/src/USER-MOFFF/angle_class2_p6.o \
./lammps-dev/src/USER-MOFFF/angle_cosine_buck6d.o \
./lammps-dev/src/USER-MOFFF/improper_inversion_harmonic.o \
./lammps-dev/src/USER-MOFFF/pair_buck6d_coul_gauss_dsf.o \
./lammps-dev/src/USER-MOFFF/pair_buck6d_coul_gauss_long.o 

CPP_DEPS += \
./lammps-dev/src/USER-MOFFF/angle_class2_p6.d \
./lammps-dev/src/USER-MOFFF/angle_cosine_buck6d.d \
./lammps-dev/src/USER-MOFFF/improper_inversion_harmonic.d \
./lammps-dev/src/USER-MOFFF/pair_buck6d_coul_gauss_dsf.d \
./lammps-dev/src/USER-MOFFF/pair_buck6d_coul_gauss_long.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-MOFFF/%.o: ../lammps-dev/src/USER-MOFFF/%.cpp lammps-dev/src/USER-MOFFF/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


