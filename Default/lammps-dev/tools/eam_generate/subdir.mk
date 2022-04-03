################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/tools/eam_generate/Al_Zhou.c \
../lammps-dev/tools/eam_generate/Cu_Mishin1.c \
../lammps-dev/tools/eam_generate/Cu_Zhou.c \
../lammps-dev/tools/eam_generate/W_Zhou.c 

OBJS += \
./lammps-dev/tools/eam_generate/Al_Zhou.o \
./lammps-dev/tools/eam_generate/Cu_Mishin1.o \
./lammps-dev/tools/eam_generate/Cu_Zhou.o \
./lammps-dev/tools/eam_generate/W_Zhou.o 

C_DEPS += \
./lammps-dev/tools/eam_generate/Al_Zhou.d \
./lammps-dev/tools/eam_generate/Cu_Mishin1.d \
./lammps-dev/tools/eam_generate/Cu_Zhou.d \
./lammps-dev/tools/eam_generate/W_Zhou.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/eam_generate/%.o: ../lammps-dev/tools/eam_generate/%.c lammps-dev/tools/eam_generate/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


