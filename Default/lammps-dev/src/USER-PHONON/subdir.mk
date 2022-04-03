################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-PHONON/dynamical_matrix.cpp \
../lammps-dev/src/USER-PHONON/fix_phonon.cpp \
../lammps-dev/src/USER-PHONON/third_order.cpp 

OBJS += \
./lammps-dev/src/USER-PHONON/dynamical_matrix.o \
./lammps-dev/src/USER-PHONON/fix_phonon.o \
./lammps-dev/src/USER-PHONON/third_order.o 

CPP_DEPS += \
./lammps-dev/src/USER-PHONON/dynamical_matrix.d \
./lammps-dev/src/USER-PHONON/fix_phonon.d \
./lammps-dev/src/USER-PHONON/third_order.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-PHONON/%.o: ../lammps-dev/src/USER-PHONON/%.cpp lammps-dev/src/USER-PHONON/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


