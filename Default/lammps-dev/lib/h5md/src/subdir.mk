################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/lib/h5md/src/ch5md.c 

OBJS += \
./lammps-dev/lib/h5md/src/ch5md.o 

C_DEPS += \
./lammps-dev/lib/h5md/src/ch5md.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/h5md/src/%.o: ../lammps-dev/lib/h5md/src/%.c lammps-dev/lib/h5md/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


