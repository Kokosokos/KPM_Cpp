################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/tools/i-pi/drivers/sockets.c 

OBJS += \
./lammps-dev/tools/i-pi/drivers/sockets.o 

C_DEPS += \
./lammps-dev/tools/i-pi/drivers/sockets.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/tools/i-pi/drivers/%.o: ../lammps-dev/tools/i-pi/drivers/%.c lammps-dev/tools/i-pi/drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


