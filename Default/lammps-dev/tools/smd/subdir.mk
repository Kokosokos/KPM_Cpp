################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/tools/smd/dump2vtk_tris.cpp 

OBJS += \
./lammps-dev/tools/smd/dump2vtk_tris.o 

CPP_DEPS += \
./lammps-dev/tools/smd/dump2vtk_tris.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/smd/%.o: ../lammps-dev/tools/smd/%.cpp lammps-dev/tools/smd/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


