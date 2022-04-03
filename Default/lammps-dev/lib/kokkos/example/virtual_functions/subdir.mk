################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/example/virtual_functions/classes.cpp \
../lammps-dev/lib/kokkos/example/virtual_functions/main.cpp 

OBJS += \
./lammps-dev/lib/kokkos/example/virtual_functions/classes.o \
./lammps-dev/lib/kokkos/example/virtual_functions/main.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/example/virtual_functions/classes.d \
./lammps-dev/lib/kokkos/example/virtual_functions/main.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/example/virtual_functions/%.o: ../lammps-dev/lib/kokkos/example/virtual_functions/%.cpp lammps-dev/lib/kokkos/example/virtual_functions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


