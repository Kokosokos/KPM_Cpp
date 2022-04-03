################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/SHOCK/fix_append_atoms.cpp \
../lammps-dev/src/SHOCK/fix_msst.cpp \
../lammps-dev/src/SHOCK/fix_nphug.cpp \
../lammps-dev/src/SHOCK/fix_wall_piston.cpp 

OBJS += \
./lammps-dev/src/SHOCK/fix_append_atoms.o \
./lammps-dev/src/SHOCK/fix_msst.o \
./lammps-dev/src/SHOCK/fix_nphug.o \
./lammps-dev/src/SHOCK/fix_wall_piston.o 

CPP_DEPS += \
./lammps-dev/src/SHOCK/fix_append_atoms.d \
./lammps-dev/src/SHOCK/fix_msst.d \
./lammps-dev/src/SHOCK/fix_nphug.d \
./lammps-dev/src/SHOCK/fix_wall_piston.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/SHOCK/%.o: ../lammps-dev/src/SHOCK/%.cpp lammps-dev/src/SHOCK/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


