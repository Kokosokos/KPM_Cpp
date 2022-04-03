################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/algorithms/unit_tests/TestCuda.cpp \
../lammps-dev/lib/kokkos/algorithms/unit_tests/TestHPX.cpp \
../lammps-dev/lib/kokkos/algorithms/unit_tests/TestOpenMP.cpp \
../lammps-dev/lib/kokkos/algorithms/unit_tests/TestROCm.cpp \
../lammps-dev/lib/kokkos/algorithms/unit_tests/TestSerial.cpp \
../lammps-dev/lib/kokkos/algorithms/unit_tests/TestThreads.cpp \
../lammps-dev/lib/kokkos/algorithms/unit_tests/UnitTestMain.cpp 

OBJS += \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestCuda.o \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestHPX.o \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestOpenMP.o \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestROCm.o \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestSerial.o \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestThreads.o \
./lammps-dev/lib/kokkos/algorithms/unit_tests/UnitTestMain.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestCuda.d \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestHPX.d \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestOpenMP.d \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestROCm.d \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestSerial.d \
./lammps-dev/lib/kokkos/algorithms/unit_tests/TestThreads.d \
./lammps-dev/lib/kokkos/algorithms/unit_tests/UnitTestMain.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/algorithms/unit_tests/%.o: ../lammps-dev/lib/kokkos/algorithms/unit_tests/%.cpp lammps-dev/lib/kokkos/algorithms/unit_tests/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


