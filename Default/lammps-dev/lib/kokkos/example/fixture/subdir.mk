################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/example/fixture/BoxElemPart.cpp \
../lammps-dev/lib/kokkos/example/fixture/Main.cpp \
../lammps-dev/lib/kokkos/example/fixture/TestFixture.cpp 

OBJS += \
./lammps-dev/lib/kokkos/example/fixture/BoxElemPart.o \
./lammps-dev/lib/kokkos/example/fixture/Main.o \
./lammps-dev/lib/kokkos/example/fixture/TestFixture.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/example/fixture/BoxElemPart.d \
./lammps-dev/lib/kokkos/example/fixture/Main.d \
./lammps-dev/lib/kokkos/example/fixture/TestFixture.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/example/fixture/%.o: ../lammps-dev/lib/kokkos/example/fixture/%.cpp lammps-dev/lib/kokkos/example/fixture/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


