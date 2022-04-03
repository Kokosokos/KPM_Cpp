################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-MANIFOLD/fix_manifoldforce.cpp \
../lammps-dev/src/USER-MANIFOLD/fix_nve_manifold_rattle.cpp \
../lammps-dev/src/USER-MANIFOLD/fix_nvt_manifold_rattle.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_cylinder.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_cylinder_dent.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_dumbbell.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_ellipsoid.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_factory.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_gaussian_bump.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_plane.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_plane_wiggle.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_spine.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_thylakoid.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_thylakoid_shared.cpp \
../lammps-dev/src/USER-MANIFOLD/manifold_torus.cpp 

OBJS += \
./lammps-dev/src/USER-MANIFOLD/fix_manifoldforce.o \
./lammps-dev/src/USER-MANIFOLD/fix_nve_manifold_rattle.o \
./lammps-dev/src/USER-MANIFOLD/fix_nvt_manifold_rattle.o \
./lammps-dev/src/USER-MANIFOLD/manifold_cylinder.o \
./lammps-dev/src/USER-MANIFOLD/manifold_cylinder_dent.o \
./lammps-dev/src/USER-MANIFOLD/manifold_dumbbell.o \
./lammps-dev/src/USER-MANIFOLD/manifold_ellipsoid.o \
./lammps-dev/src/USER-MANIFOLD/manifold_factory.o \
./lammps-dev/src/USER-MANIFOLD/manifold_gaussian_bump.o \
./lammps-dev/src/USER-MANIFOLD/manifold_plane.o \
./lammps-dev/src/USER-MANIFOLD/manifold_plane_wiggle.o \
./lammps-dev/src/USER-MANIFOLD/manifold_spine.o \
./lammps-dev/src/USER-MANIFOLD/manifold_thylakoid.o \
./lammps-dev/src/USER-MANIFOLD/manifold_thylakoid_shared.o \
./lammps-dev/src/USER-MANIFOLD/manifold_torus.o 

CPP_DEPS += \
./lammps-dev/src/USER-MANIFOLD/fix_manifoldforce.d \
./lammps-dev/src/USER-MANIFOLD/fix_nve_manifold_rattle.d \
./lammps-dev/src/USER-MANIFOLD/fix_nvt_manifold_rattle.d \
./lammps-dev/src/USER-MANIFOLD/manifold_cylinder.d \
./lammps-dev/src/USER-MANIFOLD/manifold_cylinder_dent.d \
./lammps-dev/src/USER-MANIFOLD/manifold_dumbbell.d \
./lammps-dev/src/USER-MANIFOLD/manifold_ellipsoid.d \
./lammps-dev/src/USER-MANIFOLD/manifold_factory.d \
./lammps-dev/src/USER-MANIFOLD/manifold_gaussian_bump.d \
./lammps-dev/src/USER-MANIFOLD/manifold_plane.d \
./lammps-dev/src/USER-MANIFOLD/manifold_plane_wiggle.d \
./lammps-dev/src/USER-MANIFOLD/manifold_spine.d \
./lammps-dev/src/USER-MANIFOLD/manifold_thylakoid.d \
./lammps-dev/src/USER-MANIFOLD/manifold_thylakoid_shared.d \
./lammps-dev/src/USER-MANIFOLD/manifold_torus.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-MANIFOLD/%.o: ../lammps-dev/src/USER-MANIFOLD/%.cpp lammps-dev/src/USER-MANIFOLD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


