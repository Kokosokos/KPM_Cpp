################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/MESSAGE/fix_client_md.cpp \
../lammps-dev/src/MESSAGE/message.cpp \
../lammps-dev/src/MESSAGE/server.cpp \
../lammps-dev/src/MESSAGE/server_mc.cpp \
../lammps-dev/src/MESSAGE/server_md.cpp 

OBJS += \
./lammps-dev/src/MESSAGE/fix_client_md.o \
./lammps-dev/src/MESSAGE/message.o \
./lammps-dev/src/MESSAGE/server.o \
./lammps-dev/src/MESSAGE/server_mc.o \
./lammps-dev/src/MESSAGE/server_md.o 

CPP_DEPS += \
./lammps-dev/src/MESSAGE/fix_client_md.d \
./lammps-dev/src/MESSAGE/message.d \
./lammps-dev/src/MESSAGE/server.d \
./lammps-dev/src/MESSAGE/server_mc.d \
./lammps-dev/src/MESSAGE/server_md.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/MESSAGE/%.o: ../lammps-dev/src/MESSAGE/%.cpp lammps-dev/src/MESSAGE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


