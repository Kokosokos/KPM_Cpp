################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/tools/msi2lmp/src/CheckLists.c \
../lammps-dev/tools/msi2lmp/src/GetParameters.c \
../lammps-dev/tools/msi2lmp/src/InitializeItems.c \
../lammps-dev/tools/msi2lmp/src/MakeLists.c \
../lammps-dev/tools/msi2lmp/src/ReadCarFile.c \
../lammps-dev/tools/msi2lmp/src/ReadFrcFile.c \
../lammps-dev/tools/msi2lmp/src/ReadMdfFile.c \
../lammps-dev/tools/msi2lmp/src/SearchAndFill.c \
../lammps-dev/tools/msi2lmp/src/WriteDataFile.c \
../lammps-dev/tools/msi2lmp/src/msi2lmp.c 

OBJS += \
./lammps-dev/tools/msi2lmp/src/CheckLists.o \
./lammps-dev/tools/msi2lmp/src/GetParameters.o \
./lammps-dev/tools/msi2lmp/src/InitializeItems.o \
./lammps-dev/tools/msi2lmp/src/MakeLists.o \
./lammps-dev/tools/msi2lmp/src/ReadCarFile.o \
./lammps-dev/tools/msi2lmp/src/ReadFrcFile.o \
./lammps-dev/tools/msi2lmp/src/ReadMdfFile.o \
./lammps-dev/tools/msi2lmp/src/SearchAndFill.o \
./lammps-dev/tools/msi2lmp/src/WriteDataFile.o \
./lammps-dev/tools/msi2lmp/src/msi2lmp.o 

C_DEPS += \
./lammps-dev/tools/msi2lmp/src/CheckLists.d \
./lammps-dev/tools/msi2lmp/src/GetParameters.d \
./lammps-dev/tools/msi2lmp/src/InitializeItems.d \
./lammps-dev/tools/msi2lmp/src/MakeLists.d \
./lammps-dev/tools/msi2lmp/src/ReadCarFile.d \
./lammps-dev/tools/msi2lmp/src/ReadFrcFile.d \
./lammps-dev/tools/msi2lmp/src/ReadMdfFile.d \
./lammps-dev/tools/msi2lmp/src/SearchAndFill.d \
./lammps-dev/tools/msi2lmp/src/WriteDataFile.d \
./lammps-dev/tools/msi2lmp/src/msi2lmp.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/msi2lmp/src/%.o: ../lammps-dev/tools/msi2lmp/src/%.c lammps-dev/tools/msi2lmp/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


