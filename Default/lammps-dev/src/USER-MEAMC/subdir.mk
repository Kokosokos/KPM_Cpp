################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-MEAMC/meam_dens_final.cpp \
../lammps-dev/src/USER-MEAMC/meam_dens_init.cpp \
../lammps-dev/src/USER-MEAMC/meam_force.cpp \
../lammps-dev/src/USER-MEAMC/meam_funcs.cpp \
../lammps-dev/src/USER-MEAMC/meam_impl.cpp \
../lammps-dev/src/USER-MEAMC/meam_setup_done.cpp \
../lammps-dev/src/USER-MEAMC/meam_setup_global.cpp \
../lammps-dev/src/USER-MEAMC/meam_setup_param.cpp \
../lammps-dev/src/USER-MEAMC/pair_meamc.cpp 

OBJS += \
./lammps-dev/src/USER-MEAMC/meam_dens_final.o \
./lammps-dev/src/USER-MEAMC/meam_dens_init.o \
./lammps-dev/src/USER-MEAMC/meam_force.o \
./lammps-dev/src/USER-MEAMC/meam_funcs.o \
./lammps-dev/src/USER-MEAMC/meam_impl.o \
./lammps-dev/src/USER-MEAMC/meam_setup_done.o \
./lammps-dev/src/USER-MEAMC/meam_setup_global.o \
./lammps-dev/src/USER-MEAMC/meam_setup_param.o \
./lammps-dev/src/USER-MEAMC/pair_meamc.o 

CPP_DEPS += \
./lammps-dev/src/USER-MEAMC/meam_dens_final.d \
./lammps-dev/src/USER-MEAMC/meam_dens_init.d \
./lammps-dev/src/USER-MEAMC/meam_force.d \
./lammps-dev/src/USER-MEAMC/meam_funcs.d \
./lammps-dev/src/USER-MEAMC/meam_impl.d \
./lammps-dev/src/USER-MEAMC/meam_setup_done.d \
./lammps-dev/src/USER-MEAMC/meam_setup_global.d \
./lammps-dev/src/USER-MEAMC/meam_setup_param.d \
./lammps-dev/src/USER-MEAMC/pair_meamc.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-MEAMC/%.o: ../lammps-dev/src/USER-MEAMC/%.cpp lammps-dev/src/USER-MEAMC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


