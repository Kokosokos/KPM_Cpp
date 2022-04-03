################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/tools/spin/interpolate_gneb/interpolate.c 

OBJS += \
./lammps-dev/tools/spin/interpolate_gneb/interpolate.o 

C_DEPS += \
./lammps-dev/tools/spin/interpolate_gneb/interpolate.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/spin/interpolate_gneb/%.o: ../lammps-dev/tools/spin/interpolate_gneb/%.c lammps-dev/tools/spin/interpolate_gneb/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


