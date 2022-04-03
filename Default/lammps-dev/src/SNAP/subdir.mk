################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/SNAP/compute_sna_atom.cpp \
../lammps-dev/src/SNAP/compute_snad_atom.cpp \
../lammps-dev/src/SNAP/compute_snap.cpp \
../lammps-dev/src/SNAP/compute_snav_atom.cpp \
../lammps-dev/src/SNAP/pair_snap.cpp \
../lammps-dev/src/SNAP/sna.cpp 

OBJS += \
./lammps-dev/src/SNAP/compute_sna_atom.o \
./lammps-dev/src/SNAP/compute_snad_atom.o \
./lammps-dev/src/SNAP/compute_snap.o \
./lammps-dev/src/SNAP/compute_snav_atom.o \
./lammps-dev/src/SNAP/pair_snap.o \
./lammps-dev/src/SNAP/sna.o 

CPP_DEPS += \
./lammps-dev/src/SNAP/compute_sna_atom.d \
./lammps-dev/src/SNAP/compute_snad_atom.d \
./lammps-dev/src/SNAP/compute_snap.d \
./lammps-dev/src/SNAP/compute_snav_atom.d \
./lammps-dev/src/SNAP/pair_snap.d \
./lammps-dev/src/SNAP/sna.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/SNAP/%.o: ../lammps-dev/src/SNAP/%.cpp lammps-dev/src/SNAP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


