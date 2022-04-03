################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/message/cslib/src/cslib.cpp \
../lammps-dev/lib/message/cslib/src/cslib_wrap.cpp \
../lammps-dev/lib/message/cslib/src/msg.cpp \
../lammps-dev/lib/message/cslib/src/msg_file.cpp \
../lammps-dev/lib/message/cslib/src/msg_mpi_one.cpp \
../lammps-dev/lib/message/cslib/src/msg_mpi_two.cpp \
../lammps-dev/lib/message/cslib/src/msg_zmq.cpp 

OBJS += \
./lammps-dev/lib/message/cslib/src/cslib.o \
./lammps-dev/lib/message/cslib/src/cslib_wrap.o \
./lammps-dev/lib/message/cslib/src/msg.o \
./lammps-dev/lib/message/cslib/src/msg_file.o \
./lammps-dev/lib/message/cslib/src/msg_mpi_one.o \
./lammps-dev/lib/message/cslib/src/msg_mpi_two.o \
./lammps-dev/lib/message/cslib/src/msg_zmq.o 

CPP_DEPS += \
./lammps-dev/lib/message/cslib/src/cslib.d \
./lammps-dev/lib/message/cslib/src/cslib_wrap.d \
./lammps-dev/lib/message/cslib/src/msg.d \
./lammps-dev/lib/message/cslib/src/msg_file.d \
./lammps-dev/lib/message/cslib/src/msg_mpi_one.d \
./lammps-dev/lib/message/cslib/src/msg_mpi_two.d \
./lammps-dev/lib/message/cslib/src/msg_zmq.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/message/cslib/src/%.o: ../lammps-dev/lib/message/cslib/src/%.cpp lammps-dev/lib/message/cslib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


