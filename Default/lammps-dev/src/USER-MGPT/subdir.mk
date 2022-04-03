################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-MGPT/mgpt_linalg.cpp \
../lammps-dev/src/USER-MGPT/mgpt_readpot.cpp \
../lammps-dev/src/USER-MGPT/mgpt_splinetab.cpp \
../lammps-dev/src/USER-MGPT/pair_mgpt.cpp 

OBJS += \
./lammps-dev/src/USER-MGPT/mgpt_linalg.o \
./lammps-dev/src/USER-MGPT/mgpt_readpot.o \
./lammps-dev/src/USER-MGPT/mgpt_splinetab.o \
./lammps-dev/src/USER-MGPT/pair_mgpt.o 

CPP_DEPS += \
./lammps-dev/src/USER-MGPT/mgpt_linalg.d \
./lammps-dev/src/USER-MGPT/mgpt_readpot.d \
./lammps-dev/src/USER-MGPT/mgpt_splinetab.d \
./lammps-dev/src/USER-MGPT/pair_mgpt.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-MGPT/%.o: ../lammps-dev/src/USER-MGPT/%.cpp lammps-dev/src/USER-MGPT/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


