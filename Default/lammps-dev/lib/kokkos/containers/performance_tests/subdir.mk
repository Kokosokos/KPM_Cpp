################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/containers/performance_tests/TestCuda.cpp \
../lammps-dev/lib/kokkos/containers/performance_tests/TestHPX.cpp \
../lammps-dev/lib/kokkos/containers/performance_tests/TestMain.cpp \
../lammps-dev/lib/kokkos/containers/performance_tests/TestOpenMP.cpp \
../lammps-dev/lib/kokkos/containers/performance_tests/TestROCm.cpp \
../lammps-dev/lib/kokkos/containers/performance_tests/TestThreads.cpp 

OBJS += \
./lammps-dev/lib/kokkos/containers/performance_tests/TestCuda.o \
./lammps-dev/lib/kokkos/containers/performance_tests/TestHPX.o \
./lammps-dev/lib/kokkos/containers/performance_tests/TestMain.o \
./lammps-dev/lib/kokkos/containers/performance_tests/TestOpenMP.o \
./lammps-dev/lib/kokkos/containers/performance_tests/TestROCm.o \
./lammps-dev/lib/kokkos/containers/performance_tests/TestThreads.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/containers/performance_tests/TestCuda.d \
./lammps-dev/lib/kokkos/containers/performance_tests/TestHPX.d \
./lammps-dev/lib/kokkos/containers/performance_tests/TestMain.d \
./lammps-dev/lib/kokkos/containers/performance_tests/TestOpenMP.d \
./lammps-dev/lib/kokkos/containers/performance_tests/TestROCm.d \
./lammps-dev/lib/kokkos/containers/performance_tests/TestThreads.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/containers/performance_tests/%.o: ../lammps-dev/lib/kokkos/containers/performance_tests/%.cpp lammps-dev/lib/kokkos/containers/performance_tests/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


