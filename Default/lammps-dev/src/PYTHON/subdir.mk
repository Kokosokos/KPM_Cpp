################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/PYTHON/fix_python_invoke.cpp \
../lammps-dev/src/PYTHON/fix_python_move.cpp \
../lammps-dev/src/PYTHON/pair_python.cpp \
../lammps-dev/src/PYTHON/python_impl.cpp 

OBJS += \
./lammps-dev/src/PYTHON/fix_python_invoke.o \
./lammps-dev/src/PYTHON/fix_python_move.o \
./lammps-dev/src/PYTHON/pair_python.o \
./lammps-dev/src/PYTHON/python_impl.o 

CPP_DEPS += \
./lammps-dev/src/PYTHON/fix_python_invoke.d \
./lammps-dev/src/PYTHON/fix_python_move.d \
./lammps-dev/src/PYTHON/pair_python.d \
./lammps-dev/src/PYTHON/python_impl.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/PYTHON/%.o: ../lammps-dev/src/PYTHON/%.cpp lammps-dev/src/PYTHON/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


