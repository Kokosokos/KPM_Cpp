################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/MC/fix_atom_swap.cpp \
../lammps-dev/src/MC/fix_bond_break.cpp \
../lammps-dev/src/MC/fix_bond_create.cpp \
../lammps-dev/src/MC/fix_bond_create_angle.cpp \
../lammps-dev/src/MC/fix_bond_swap.cpp \
../lammps-dev/src/MC/fix_gcmc.cpp \
../lammps-dev/src/MC/fix_tfmc.cpp \
../lammps-dev/src/MC/fix_widom.cpp \
../lammps-dev/src/MC/pair_dsmc.cpp 

OBJS += \
./lammps-dev/src/MC/fix_atom_swap.o \
./lammps-dev/src/MC/fix_bond_break.o \
./lammps-dev/src/MC/fix_bond_create.o \
./lammps-dev/src/MC/fix_bond_create_angle.o \
./lammps-dev/src/MC/fix_bond_swap.o \
./lammps-dev/src/MC/fix_gcmc.o \
./lammps-dev/src/MC/fix_tfmc.o \
./lammps-dev/src/MC/fix_widom.o \
./lammps-dev/src/MC/pair_dsmc.o 

CPP_DEPS += \
./lammps-dev/src/MC/fix_atom_swap.d \
./lammps-dev/src/MC/fix_bond_break.d \
./lammps-dev/src/MC/fix_bond_create.d \
./lammps-dev/src/MC/fix_bond_create_angle.d \
./lammps-dev/src/MC/fix_bond_swap.d \
./lammps-dev/src/MC/fix_gcmc.d \
./lammps-dev/src/MC/fix_tfmc.d \
./lammps-dev/src/MC/fix_widom.d \
./lammps-dev/src/MC/pair_dsmc.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/MC/%.o: ../lammps-dev/src/MC/%.cpp lammps-dev/src/MC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


