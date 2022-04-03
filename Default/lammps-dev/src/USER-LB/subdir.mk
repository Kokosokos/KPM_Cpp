################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/USER-LB/fix_lb_fluid.cpp \
../lammps-dev/src/USER-LB/fix_lb_momentum.cpp \
../lammps-dev/src/USER-LB/fix_lb_pc.cpp \
../lammps-dev/src/USER-LB/fix_lb_rigid_pc_sphere.cpp \
../lammps-dev/src/USER-LB/fix_lb_viscous.cpp 

OBJS += \
./lammps-dev/src/USER-LB/fix_lb_fluid.o \
./lammps-dev/src/USER-LB/fix_lb_momentum.o \
./lammps-dev/src/USER-LB/fix_lb_pc.o \
./lammps-dev/src/USER-LB/fix_lb_rigid_pc_sphere.o \
./lammps-dev/src/USER-LB/fix_lb_viscous.o 

CPP_DEPS += \
./lammps-dev/src/USER-LB/fix_lb_fluid.d \
./lammps-dev/src/USER-LB/fix_lb_momentum.d \
./lammps-dev/src/USER-LB/fix_lb_pc.d \
./lammps-dev/src/USER-LB/fix_lb_rigid_pc_sphere.d \
./lammps-dev/src/USER-LB/fix_lb_viscous.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/USER-LB/%.o: ../lammps-dev/src/USER-LB/%.cpp lammps-dev/src/USER-LB/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


