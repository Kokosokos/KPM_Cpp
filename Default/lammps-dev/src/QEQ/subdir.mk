################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/QEQ/fix_qeq.cpp \
../lammps-dev/src/QEQ/fix_qeq_dynamic.cpp \
../lammps-dev/src/QEQ/fix_qeq_fire.cpp \
../lammps-dev/src/QEQ/fix_qeq_point.cpp \
../lammps-dev/src/QEQ/fix_qeq_shielded.cpp \
../lammps-dev/src/QEQ/fix_qeq_slater.cpp 

OBJS += \
./lammps-dev/src/QEQ/fix_qeq.o \
./lammps-dev/src/QEQ/fix_qeq_dynamic.o \
./lammps-dev/src/QEQ/fix_qeq_fire.o \
./lammps-dev/src/QEQ/fix_qeq_point.o \
./lammps-dev/src/QEQ/fix_qeq_shielded.o \
./lammps-dev/src/QEQ/fix_qeq_slater.o 

CPP_DEPS += \
./lammps-dev/src/QEQ/fix_qeq.d \
./lammps-dev/src/QEQ/fix_qeq_dynamic.d \
./lammps-dev/src/QEQ/fix_qeq_fire.d \
./lammps-dev/src/QEQ/fix_qeq_point.d \
./lammps-dev/src/QEQ/fix_qeq_shielded.d \
./lammps-dev/src/QEQ/fix_qeq_slater.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/QEQ/%.o: ../lammps-dev/src/QEQ/%.cpp lammps-dev/src/QEQ/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


