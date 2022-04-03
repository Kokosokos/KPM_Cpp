################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/src/DEPEND/fastdep.c 

OBJS += \
./lammps-dev/src/DEPEND/fastdep.o 

C_DEPS += \
./lammps-dev/src/DEPEND/fastdep.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/DEPEND/%.o: ../lammps-dev/src/DEPEND/%.c lammps-dev/src/DEPEND/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


