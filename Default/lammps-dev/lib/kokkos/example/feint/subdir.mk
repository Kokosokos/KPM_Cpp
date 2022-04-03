################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/example/feint/feint_cuda.cpp \
../lammps-dev/lib/kokkos/example/feint/feint_hpx.cpp \
../lammps-dev/lib/kokkos/example/feint/feint_openmp.cpp \
../lammps-dev/lib/kokkos/example/feint/feint_rocm.cpp \
../lammps-dev/lib/kokkos/example/feint/feint_serial.cpp \
../lammps-dev/lib/kokkos/example/feint/feint_threads.cpp \
../lammps-dev/lib/kokkos/example/feint/main.cpp 

OBJS += \
./lammps-dev/lib/kokkos/example/feint/feint_cuda.o \
./lammps-dev/lib/kokkos/example/feint/feint_hpx.o \
./lammps-dev/lib/kokkos/example/feint/feint_openmp.o \
./lammps-dev/lib/kokkos/example/feint/feint_rocm.o \
./lammps-dev/lib/kokkos/example/feint/feint_serial.o \
./lammps-dev/lib/kokkos/example/feint/feint_threads.o \
./lammps-dev/lib/kokkos/example/feint/main.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/example/feint/feint_cuda.d \
./lammps-dev/lib/kokkos/example/feint/feint_hpx.d \
./lammps-dev/lib/kokkos/example/feint/feint_openmp.d \
./lammps-dev/lib/kokkos/example/feint/feint_rocm.d \
./lammps-dev/lib/kokkos/example/feint/feint_serial.d \
./lammps-dev/lib/kokkos/example/feint/feint_threads.d \
./lammps-dev/lib/kokkos/example/feint/main.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/example/feint/%.o: ../lammps-dev/lib/kokkos/example/feint/%.cpp lammps-dev/lib/kokkos/example/feint/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


