################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/MPIIO/dump_atom_mpiio.cpp \
../lammps-dev/src/MPIIO/dump_cfg_mpiio.cpp \
../lammps-dev/src/MPIIO/dump_custom_mpiio.cpp \
../lammps-dev/src/MPIIO/dump_xyz_mpiio.cpp \
../lammps-dev/src/MPIIO/restart_mpiio.cpp 

OBJS += \
./lammps-dev/src/MPIIO/dump_atom_mpiio.o \
./lammps-dev/src/MPIIO/dump_cfg_mpiio.o \
./lammps-dev/src/MPIIO/dump_custom_mpiio.o \
./lammps-dev/src/MPIIO/dump_xyz_mpiio.o \
./lammps-dev/src/MPIIO/restart_mpiio.o 

CPP_DEPS += \
./lammps-dev/src/MPIIO/dump_atom_mpiio.d \
./lammps-dev/src/MPIIO/dump_cfg_mpiio.d \
./lammps-dev/src/MPIIO/dump_custom_mpiio.d \
./lammps-dev/src/MPIIO/dump_xyz_mpiio.d \
./lammps-dev/src/MPIIO/restart_mpiio.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/MPIIO/%.o: ../lammps-dev/src/MPIIO/%.cpp lammps-dev/src/MPIIO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


