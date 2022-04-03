################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/example/global_2_local_ids/G2L_Main.cpp 

OBJS += \
./lammps-dev/lib/kokkos/example/global_2_local_ids/G2L_Main.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/example/global_2_local_ids/G2L_Main.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/example/global_2_local_ids/%.o: ../lammps-dev/lib/kokkos/example/global_2_local_ids/%.cpp lammps-dev/lib/kokkos/example/global_2_local_ids/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


