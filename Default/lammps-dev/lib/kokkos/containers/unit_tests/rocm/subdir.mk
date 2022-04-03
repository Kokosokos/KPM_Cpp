################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_BitSet.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DualView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_generic.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_rank12345.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_rank67.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynamicView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ErrorReporter.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ScatterView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_StaticCrsGraph.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_UnorderedMap.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_Vector.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ViewCtorPropEmbeddedDim.cpp 

OBJS += \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_BitSet.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DualView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_generic.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_rank12345.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_rank67.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynamicView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ErrorReporter.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ScatterView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_StaticCrsGraph.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_UnorderedMap.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_Vector.o \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ViewCtorPropEmbeddedDim.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_BitSet.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DualView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_generic.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_rank12345.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynRankViewAPI_rank67.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_DynamicView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ErrorReporter.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ScatterView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_StaticCrsGraph.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_UnorderedMap.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_Vector.d \
./lammps-dev/lib/kokkos/containers/unit_tests/rocm/TestROCm_ViewCtorPropEmbeddedDim.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/containers/unit_tests/rocm/%.o: ../lammps-dev/lib/kokkos/containers/unit_tests/rocm/%.cpp lammps-dev/lib/kokkos/containers/unit_tests/rocm/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


