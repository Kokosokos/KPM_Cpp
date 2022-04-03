################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lammps-dev/lib/qmmm/libqmmm.c \
../lammps-dev/lib/qmmm/pwqmmm.c 

OBJS += \
./lammps-dev/lib/qmmm/libqmmm.o \
./lammps-dev/lib/qmmm/pwqmmm.o 

C_DEPS += \
./lammps-dev/lib/qmmm/libqmmm.d \
./lammps-dev/lib/qmmm/pwqmmm.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/qmmm/%.o: ../lammps-dev/lib/qmmm/%.c lammps-dev/lib/qmmm/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


