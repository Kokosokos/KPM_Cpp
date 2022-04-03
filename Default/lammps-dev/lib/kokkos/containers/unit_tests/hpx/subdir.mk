################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_BitSet.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DualView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_generic.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_rank12345.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_rank67.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynamicView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ErrorReporter.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_OffsetView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ScatterView.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_StaticCrsGraph.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_UnorderedMap.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_Vector.cpp \
../lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ViewCtorPropEmbeddedDim.cpp 

OBJS += \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_BitSet.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DualView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_generic.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_rank12345.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_rank67.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynamicView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ErrorReporter.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_OffsetView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ScatterView.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_StaticCrsGraph.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_UnorderedMap.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_Vector.o \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ViewCtorPropEmbeddedDim.o 

CPP_DEPS += \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_BitSet.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DualView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_generic.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_rank12345.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynRankViewAPI_rank67.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_DynamicView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ErrorReporter.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_OffsetView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ScatterView.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_StaticCrsGraph.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_UnorderedMap.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_Vector.d \
./lammps-dev/lib/kokkos/containers/unit_tests/hpx/TestHPX_ViewCtorPropEmbeddedDim.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/kokkos/containers/unit_tests/hpx/%.o: ../lammps-dev/lib/kokkos/containers/unit_tests/hpx/%.cpp lammps-dev/lib/kokkos/containers/unit_tests/hpx/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


