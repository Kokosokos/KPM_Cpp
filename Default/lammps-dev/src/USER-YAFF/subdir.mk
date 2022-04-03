################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-YAFF/angle_cross.cpp \
../lammps-dev/src/USER-YAFF/angle_mm3.cpp \
../lammps-dev/src/USER-YAFF/bond_mm3.cpp \
../lammps-dev/src/USER-YAFF/improper_distharm.cpp \
../lammps-dev/src/USER-YAFF/improper_sqdistharm.cpp \
../lammps-dev/src/USER-YAFF/pair_lj_switch3_coulgauss_long.cpp \
../lammps-dev/src/USER-YAFF/pair_mm3_switch3_coulgauss_long.cpp 

OBJS += \
./lammps-dev/src/USER-YAFF/angle_cross.o \
./lammps-dev/src/USER-YAFF/angle_mm3.o \
./lammps-dev/src/USER-YAFF/bond_mm3.o \
./lammps-dev/src/USER-YAFF/improper_distharm.o \
./lammps-dev/src/USER-YAFF/improper_sqdistharm.o \
./lammps-dev/src/USER-YAFF/pair_lj_switch3_coulgauss_long.o \
./lammps-dev/src/USER-YAFF/pair_mm3_switch3_coulgauss_long.o 

CPP_DEPS += \
./lammps-dev/src/USER-YAFF/angle_cross.d \
./lammps-dev/src/USER-YAFF/angle_mm3.d \
./lammps-dev/src/USER-YAFF/bond_mm3.d \
./lammps-dev/src/USER-YAFF/improper_distharm.d \
./lammps-dev/src/USER-YAFF/improper_sqdistharm.d \
./lammps-dev/src/USER-YAFF/pair_lj_switch3_coulgauss_long.d \
./lammps-dev/src/USER-YAFF/pair_mm3_switch3_coulgauss_long.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-YAFF/%.o: ../lammps-dev/src/USER-YAFF/%.cpp lammps-dev/src/USER-YAFF/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


