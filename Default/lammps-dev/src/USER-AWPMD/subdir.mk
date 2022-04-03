################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-AWPMD/atom_vec_wavepacket.cpp \
../lammps-dev/src/USER-AWPMD/fix_nve_awpmd.cpp \
../lammps-dev/src/USER-AWPMD/pair_awpmd_cut.cpp 

OBJS += \
./lammps-dev/src/USER-AWPMD/atom_vec_wavepacket.o \
./lammps-dev/src/USER-AWPMD/fix_nve_awpmd.o \
./lammps-dev/src/USER-AWPMD/pair_awpmd_cut.o 

CPP_DEPS += \
./lammps-dev/src/USER-AWPMD/atom_vec_wavepacket.d \
./lammps-dev/src/USER-AWPMD/fix_nve_awpmd.d \
./lammps-dev/src/USER-AWPMD/pair_awpmd_cut.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-AWPMD/%.o: ../lammps-dev/src/USER-AWPMD/%.cpp lammps-dev/src/USER-AWPMD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


