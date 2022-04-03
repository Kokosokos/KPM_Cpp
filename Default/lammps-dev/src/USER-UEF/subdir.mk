################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-UEF/compute_pressure_uef.cpp \
../lammps-dev/src/USER-UEF/compute_temp_uef.cpp \
../lammps-dev/src/USER-UEF/dump_cfg_uef.cpp \
../lammps-dev/src/USER-UEF/fix_nh_uef.cpp \
../lammps-dev/src/USER-UEF/fix_npt_uef.cpp \
../lammps-dev/src/USER-UEF/fix_nvt_uef.cpp \
../lammps-dev/src/USER-UEF/uef_utils.cpp 

OBJS += \
./lammps-dev/src/USER-UEF/compute_pressure_uef.o \
./lammps-dev/src/USER-UEF/compute_temp_uef.o \
./lammps-dev/src/USER-UEF/dump_cfg_uef.o \
./lammps-dev/src/USER-UEF/fix_nh_uef.o \
./lammps-dev/src/USER-UEF/fix_npt_uef.o \
./lammps-dev/src/USER-UEF/fix_nvt_uef.o \
./lammps-dev/src/USER-UEF/uef_utils.o 

CPP_DEPS += \
./lammps-dev/src/USER-UEF/compute_pressure_uef.d \
./lammps-dev/src/USER-UEF/compute_temp_uef.d \
./lammps-dev/src/USER-UEF/dump_cfg_uef.d \
./lammps-dev/src/USER-UEF/fix_nh_uef.d \
./lammps-dev/src/USER-UEF/fix_npt_uef.d \
./lammps-dev/src/USER-UEF/fix_nvt_uef.d \
./lammps-dev/src/USER-UEF/uef_utils.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-UEF/%.o: ../lammps-dev/src/USER-UEF/%.cpp lammps-dev/src/USER-UEF/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


