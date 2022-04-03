################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/MLIAP/compute_mliap.cpp \
../lammps-dev/src/MLIAP/mliap_data.cpp \
../lammps-dev/src/MLIAP/mliap_descriptor.cpp \
../lammps-dev/src/MLIAP/mliap_descriptor_snap.cpp \
../lammps-dev/src/MLIAP/mliap_model.cpp \
../lammps-dev/src/MLIAP/mliap_model_linear.cpp \
../lammps-dev/src/MLIAP/mliap_model_nn.cpp \
../lammps-dev/src/MLIAP/mliap_model_python.cpp \
../lammps-dev/src/MLIAP/mliap_model_quadratic.cpp \
../lammps-dev/src/MLIAP/pair_mliap.cpp 

OBJS += \
./lammps-dev/src/MLIAP/compute_mliap.o \
./lammps-dev/src/MLIAP/mliap_data.o \
./lammps-dev/src/MLIAP/mliap_descriptor.o \
./lammps-dev/src/MLIAP/mliap_descriptor_snap.o \
./lammps-dev/src/MLIAP/mliap_model.o \
./lammps-dev/src/MLIAP/mliap_model_linear.o \
./lammps-dev/src/MLIAP/mliap_model_nn.o \
./lammps-dev/src/MLIAP/mliap_model_python.o \
./lammps-dev/src/MLIAP/mliap_model_quadratic.o \
./lammps-dev/src/MLIAP/pair_mliap.o 

CPP_DEPS += \
./lammps-dev/src/MLIAP/compute_mliap.d \
./lammps-dev/src/MLIAP/mliap_data.d \
./lammps-dev/src/MLIAP/mliap_descriptor.d \
./lammps-dev/src/MLIAP/mliap_descriptor_snap.d \
./lammps-dev/src/MLIAP/mliap_model.d \
./lammps-dev/src/MLIAP/mliap_model_linear.d \
./lammps-dev/src/MLIAP/mliap_model_nn.d \
./lammps-dev/src/MLIAP/mliap_model_python.d \
./lammps-dev/src/MLIAP/mliap_model_quadratic.d \
./lammps-dev/src/MLIAP/pair_mliap.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/MLIAP/%.o: ../lammps-dev/src/MLIAP/%.cpp lammps-dev/src/MLIAP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


