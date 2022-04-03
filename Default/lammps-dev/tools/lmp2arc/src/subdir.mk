################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/tools/lmp2arc/src/ProcessPosFile01.c \
../lammps-dev/tools/lmp2arc/src/ProcessPosFile05.c \
../lammps-dev/tools/lmp2arc/src/ReadCarFile.c \
../lammps-dev/tools/lmp2arc/src/WriteArcFrame.c \
../lammps-dev/tools/lmp2arc/src/lmp2arc.c \
../lammps-dev/tools/lmp2arc/src/unwrap_molecules.c 

OBJS += \
./lammps-dev/tools/lmp2arc/src/ProcessPosFile01.o \
./lammps-dev/tools/lmp2arc/src/ProcessPosFile05.o \
./lammps-dev/tools/lmp2arc/src/ReadCarFile.o \
./lammps-dev/tools/lmp2arc/src/WriteArcFrame.o \
./lammps-dev/tools/lmp2arc/src/lmp2arc.o \
./lammps-dev/tools/lmp2arc/src/unwrap_molecules.o 

C_DEPS += \
./lammps-dev/tools/lmp2arc/src/ProcessPosFile01.d \
./lammps-dev/tools/lmp2arc/src/ProcessPosFile05.d \
./lammps-dev/tools/lmp2arc/src/ReadCarFile.d \
./lammps-dev/tools/lmp2arc/src/WriteArcFrame.d \
./lammps-dev/tools/lmp2arc/src/lmp2arc.d \
./lammps-dev/tools/lmp2arc/src/unwrap_molecules.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/lmp2arc/src/%.o: ../lammps-dev/tools/lmp2arc/src/%.c lammps-dev/tools/lmp2arc/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


