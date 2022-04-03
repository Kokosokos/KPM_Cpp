################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/gpu/geryon/ucl_get_devices.cpp 

OBJS += \
./lammps-dev/lib/gpu/geryon/ucl_get_devices.o 

CPP_DEPS += \
./lammps-dev/lib/gpu/geryon/ucl_get_devices.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/gpu/geryon/%.o: ../lammps-dev/lib/gpu/geryon/%.cpp lammps-dev/lib/gpu/geryon/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


