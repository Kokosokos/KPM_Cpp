################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_BitSet.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DualView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_generic.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_rank12345.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_rank67.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynamicView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ErrorReporter.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_OffsetView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ScatterView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_StaticCrsGraph.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_UnorderedMap.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_Vector.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ViewCtorPropEmbeddedDim.cpp 

OBJS += \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_BitSet.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DualView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_generic.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_rank12345.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_rank67.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynamicView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ErrorReporter.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_OffsetView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ScatterView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_StaticCrsGraph.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_UnorderedMap.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_Vector.o \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ViewCtorPropEmbeddedDim.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_BitSet.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DualView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_generic.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_rank12345.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynRankViewAPI_rank67.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_DynamicView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ErrorReporter.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_OffsetView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ScatterView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_StaticCrsGraph.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_UnorderedMap.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_Vector.d \
./lammps-dev/lib/kokkos/containers/unit_tests/openmp/TestOpenMP_ViewCtorPropEmbeddedDim.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/containers/unit_tests/openmp/%.o: ../lammps-dev/lib/kokkos/containers/unit_tests/openmp/%.cpp lammps-dev/lib/kokkos/containers/unit_tests/openmp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


