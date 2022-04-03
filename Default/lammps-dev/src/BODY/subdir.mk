################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/BODY/body_nparticle.cpp \
../lammps-dev/src/BODY/body_rounded_polygon.cpp \
../lammps-dev/src/BODY/body_rounded_polyhedron.cpp \
../lammps-dev/src/BODY/compute_body_local.cpp \
../lammps-dev/src/BODY/compute_temp_body.cpp \
../lammps-dev/src/BODY/fix_nh_body.cpp \
../lammps-dev/src/BODY/fix_nph_body.cpp \
../lammps-dev/src/BODY/fix_npt_body.cpp \
../lammps-dev/src/BODY/fix_nve_body.cpp \
../lammps-dev/src/BODY/fix_nvt_body.cpp \
../lammps-dev/src/BODY/fix_wall_body_polygon.cpp \
../lammps-dev/src/BODY/fix_wall_body_polyhedron.cpp \
../lammps-dev/src/BODY/pair_body_nparticle.cpp \
../lammps-dev/src/BODY/pair_body_rounded_polygon.cpp \
../lammps-dev/src/BODY/pair_body_rounded_polyhedron.cpp 

OBJS += \
./lammps-dev/src/BODY/body_nparticle.o \
./lammps-dev/src/BODY/body_rounded_polygon.o \
./lammps-dev/src/BODY/body_rounded_polyhedron.o \
./lammps-dev/src/BODY/compute_body_local.o \
./lammps-dev/src/BODY/compute_temp_body.o \
./lammps-dev/src/BODY/fix_nh_body.o \
./lammps-dev/src/BODY/fix_nph_body.o \
./lammps-dev/src/BODY/fix_npt_body.o \
./lammps-dev/src/BODY/fix_nve_body.o \
./lammps-dev/src/BODY/fix_nvt_body.o \
./lammps-dev/src/BODY/fix_wall_body_polygon.o \
./lammps-dev/src/BODY/fix_wall_body_polyhedron.o \
./lammps-dev/src/BODY/pair_body_nparticle.o \
./lammps-dev/src/BODY/pair_body_rounded_polygon.o \
./lammps-dev/src/BODY/pair_body_rounded_polyhedron.o 

CPP_DEPS += \
./lammps-dev/src/BODY/body_nparticle.d \
./lammps-dev/src/BODY/body_rounded_polygon.d \
./lammps-dev/src/BODY/body_rounded_polyhedron.d \
./lammps-dev/src/BODY/compute_body_local.d \
./lammps-dev/src/BODY/compute_temp_body.d \
./lammps-dev/src/BODY/fix_nh_body.d \
./lammps-dev/src/BODY/fix_nph_body.d \
./lammps-dev/src/BODY/fix_npt_body.d \
./lammps-dev/src/BODY/fix_nve_body.d \
./lammps-dev/src/BODY/fix_nvt_body.d \
./lammps-dev/src/BODY/fix_wall_body_polygon.d \
./lammps-dev/src/BODY/fix_wall_body_polyhedron.d \
./lammps-dev/src/BODY/pair_body_nparticle.d \
./lammps-dev/src/BODY/pair_body_rounded_polygon.d \
./lammps-dev/src/BODY/pair_body_rounded_polyhedron.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/BODY/%.o: ../lammps-dev/src/BODY/%.cpp lammps-dev/src/BODY/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


