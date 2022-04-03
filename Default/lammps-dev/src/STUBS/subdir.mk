################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/STUBS/mpi.cpp 

C_SRCS += \
../lammps-dev/src/STUBS/mpi.c 

O_SRCS += \
../lammps-dev/src/STUBS/mpi.o 

OBJS += \
./lammps-dev/src/STUBS/mpi.o 

CPP_DEPS += \
./lammps-dev/src/STUBS/mpi.d 

C_DEPS += \
./lammps-dev/src/STUBS/mpi.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/STUBS/%.o: ../lammps-dev/src/STUBS/%.c lammps-dev/src/STUBS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

lammps-dev/src/STUBS/%.o: ../lammps-dev/src/STUBS/%.cpp lammps-dev/src/STUBS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


