################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/COLLOID/fix_wall_colloid.cpp \
../lammps-dev/src/COLLOID/pair_brownian.cpp \
../lammps-dev/src/COLLOID/pair_brownian_poly.cpp \
../lammps-dev/src/COLLOID/pair_colloid.cpp \
../lammps-dev/src/COLLOID/pair_lubricate.cpp \
../lammps-dev/src/COLLOID/pair_lubricateU.cpp \
../lammps-dev/src/COLLOID/pair_lubricateU_poly.cpp \
../lammps-dev/src/COLLOID/pair_lubricate_poly.cpp \
../lammps-dev/src/COLLOID/pair_yukawa_colloid.cpp 

OBJS += \
./lammps-dev/src/COLLOID/fix_wall_colloid.o \
./lammps-dev/src/COLLOID/pair_brownian.o \
./lammps-dev/src/COLLOID/pair_brownian_poly.o \
./lammps-dev/src/COLLOID/pair_colloid.o \
./lammps-dev/src/COLLOID/pair_lubricate.o \
./lammps-dev/src/COLLOID/pair_lubricateU.o \
./lammps-dev/src/COLLOID/pair_lubricateU_poly.o \
./lammps-dev/src/COLLOID/pair_lubricate_poly.o \
./lammps-dev/src/COLLOID/pair_yukawa_colloid.o 

CPP_DEPS += \
./lammps-dev/src/COLLOID/fix_wall_colloid.d \
./lammps-dev/src/COLLOID/pair_brownian.d \
./lammps-dev/src/COLLOID/pair_brownian_poly.d \
./lammps-dev/src/COLLOID/pair_colloid.d \
./lammps-dev/src/COLLOID/pair_lubricate.d \
./lammps-dev/src/COLLOID/pair_lubricateU.d \
./lammps-dev/src/COLLOID/pair_lubricateU_poly.d \
./lammps-dev/src/COLLOID/pair_lubricate_poly.d \
./lammps-dev/src/COLLOID/pair_yukawa_colloid.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/COLLOID/%.o: ../lammps-dev/src/COLLOID/%.cpp lammps-dev/src/COLLOID/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


