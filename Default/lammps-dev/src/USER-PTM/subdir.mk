################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-PTM/compute_ptm_atom.cpp \
../lammps-dev/src/USER-PTM/ptm_alloy_types.cpp \
../lammps-dev/src/USER-PTM/ptm_canonical_coloured.cpp \
../lammps-dev/src/USER-PTM/ptm_constants.cpp \
../lammps-dev/src/USER-PTM/ptm_convex_hull_incremental.cpp \
../lammps-dev/src/USER-PTM/ptm_deformation_gradient.cpp \
../lammps-dev/src/USER-PTM/ptm_graph_data.cpp \
../lammps-dev/src/USER-PTM/ptm_graph_tools.cpp \
../lammps-dev/src/USER-PTM/ptm_index.cpp \
../lammps-dev/src/USER-PTM/ptm_initialize_data.cpp \
../lammps-dev/src/USER-PTM/ptm_neighbour_ordering.cpp \
../lammps-dev/src/USER-PTM/ptm_normalize_vertices.cpp \
../lammps-dev/src/USER-PTM/ptm_polar.cpp \
../lammps-dev/src/USER-PTM/ptm_quat.cpp \
../lammps-dev/src/USER-PTM/ptm_structure_matcher.cpp \
../lammps-dev/src/USER-PTM/ptm_voronoi_cell.cpp 

OBJS += \
./lammps-dev/src/USER-PTM/compute_ptm_atom.o \
./lammps-dev/src/USER-PTM/ptm_alloy_types.o \
./lammps-dev/src/USER-PTM/ptm_canonical_coloured.o \
./lammps-dev/src/USER-PTM/ptm_constants.o \
./lammps-dev/src/USER-PTM/ptm_convex_hull_incremental.o \
./lammps-dev/src/USER-PTM/ptm_deformation_gradient.o \
./lammps-dev/src/USER-PTM/ptm_graph_data.o \
./lammps-dev/src/USER-PTM/ptm_graph_tools.o \
./lammps-dev/src/USER-PTM/ptm_index.o \
./lammps-dev/src/USER-PTM/ptm_initialize_data.o \
./lammps-dev/src/USER-PTM/ptm_neighbour_ordering.o \
./lammps-dev/src/USER-PTM/ptm_normalize_vertices.o \
./lammps-dev/src/USER-PTM/ptm_polar.o \
./lammps-dev/src/USER-PTM/ptm_quat.o \
./lammps-dev/src/USER-PTM/ptm_structure_matcher.o \
./lammps-dev/src/USER-PTM/ptm_voronoi_cell.o 

CPP_DEPS += \
./lammps-dev/src/USER-PTM/compute_ptm_atom.d \
./lammps-dev/src/USER-PTM/ptm_alloy_types.d \
./lammps-dev/src/USER-PTM/ptm_canonical_coloured.d \
./lammps-dev/src/USER-PTM/ptm_constants.d \
./lammps-dev/src/USER-PTM/ptm_convex_hull_incremental.d \
./lammps-dev/src/USER-PTM/ptm_deformation_gradient.d \
./lammps-dev/src/USER-PTM/ptm_graph_data.d \
./lammps-dev/src/USER-PTM/ptm_graph_tools.d \
./lammps-dev/src/USER-PTM/ptm_index.d \
./lammps-dev/src/USER-PTM/ptm_initialize_data.d \
./lammps-dev/src/USER-PTM/ptm_neighbour_ordering.d \
./lammps-dev/src/USER-PTM/ptm_normalize_vertices.d \
./lammps-dev/src/USER-PTM/ptm_polar.d \
./lammps-dev/src/USER-PTM/ptm_quat.d \
./lammps-dev/src/USER-PTM/ptm_structure_matcher.d \
./lammps-dev/src/USER-PTM/ptm_voronoi_cell.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-PTM/%.o: ../lammps-dev/src/USER-PTM/%.cpp lammps-dev/src/USER-PTM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


