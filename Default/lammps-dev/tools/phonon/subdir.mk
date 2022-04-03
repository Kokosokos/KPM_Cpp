################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/tools/phonon/disp.cpp \
../lammps-dev/tools/phonon/dynmat.cpp \
../lammps-dev/tools/phonon/green.cpp \
../lammps-dev/tools/phonon/interpolate.cpp \
../lammps-dev/tools/phonon/main.cpp \
../lammps-dev/tools/phonon/memory.cpp \
../lammps-dev/tools/phonon/phonon.cpp \
../lammps-dev/tools/phonon/timer.cpp 

OBJS += \
./lammps-dev/tools/phonon/disp.o \
./lammps-dev/tools/phonon/dynmat.o \
./lammps-dev/tools/phonon/green.o \
./lammps-dev/tools/phonon/interpolate.o \
./lammps-dev/tools/phonon/main.o \
./lammps-dev/tools/phonon/memory.o \
./lammps-dev/tools/phonon/phonon.o \
./lammps-dev/tools/phonon/timer.o 

CPP_DEPS += \
./lammps-dev/tools/phonon/disp.d \
./lammps-dev/tools/phonon/dynmat.d \
./lammps-dev/tools/phonon/green.d \
./lammps-dev/tools/phonon/interpolate.d \
./lammps-dev/tools/phonon/main.d \
./lammps-dev/tools/phonon/memory.d \
./lammps-dev/tools/phonon/phonon.d \
./lammps-dev/tools/phonon/timer.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/phonon/%.o: ../lammps-dev/tools/phonon/%.cpp lammps-dev/tools/phonon/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


