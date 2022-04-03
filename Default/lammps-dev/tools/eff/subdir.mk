################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/tools/eff/restart2data-pEFF.cpp 

C_SRCS += \
../lammps-dev/tools/eff/lmp2radii.c 

OBJS += \
./lammps-dev/tools/eff/lmp2radii.o \
./lammps-dev/tools/eff/restart2data-pEFF.o 

CPP_DEPS += \
./lammps-dev/tools/eff/restart2data-pEFF.d 

C_DEPS += \
./lammps-dev/tools/eff/lmp2radii.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/eff/%.o: ../lammps-dev/tools/eff/%.c lammps-dev/tools/eff/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

lammps-dev/tools/eff/%.o: ../lammps-dev/tools/eff/%.cpp lammps-dev/tools/eff/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


