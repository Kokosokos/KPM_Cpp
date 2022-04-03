################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/GRANULAR/fix_freeze.cpp \
../lammps-dev/src/GRANULAR/fix_pour.cpp \
../lammps-dev/src/GRANULAR/fix_wall_gran.cpp \
../lammps-dev/src/GRANULAR/fix_wall_gran_region.cpp \
../lammps-dev/src/GRANULAR/pair_gran_hertz_history.cpp \
../lammps-dev/src/GRANULAR/pair_gran_hooke.cpp \
../lammps-dev/src/GRANULAR/pair_gran_hooke_history.cpp \
../lammps-dev/src/GRANULAR/pair_granular.cpp 

OBJS += \
./lammps-dev/src/GRANULAR/fix_freeze.o \
./lammps-dev/src/GRANULAR/fix_pour.o \
./lammps-dev/src/GRANULAR/fix_wall_gran.o \
./lammps-dev/src/GRANULAR/fix_wall_gran_region.o \
./lammps-dev/src/GRANULAR/pair_gran_hertz_history.o \
./lammps-dev/src/GRANULAR/pair_gran_hooke.o \
./lammps-dev/src/GRANULAR/pair_gran_hooke_history.o \
./lammps-dev/src/GRANULAR/pair_granular.o 

CPP_DEPS += \
./lammps-dev/src/GRANULAR/fix_freeze.d \
./lammps-dev/src/GRANULAR/fix_pour.d \
./lammps-dev/src/GRANULAR/fix_wall_gran.d \
./lammps-dev/src/GRANULAR/fix_wall_gran_region.d \
./lammps-dev/src/GRANULAR/pair_gran_hertz_history.d \
./lammps-dev/src/GRANULAR/pair_gran_hooke.d \
./lammps-dev/src/GRANULAR/pair_gran_hooke_history.d \
./lammps-dev/src/GRANULAR/pair_granular.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/GRANULAR/%.o: ../lammps-dev/src/GRANULAR/%.cpp lammps-dev/src/GRANULAR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


