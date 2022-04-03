################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/ASPHERE/compute_erotate_asphere.cpp \
../lammps-dev/src/ASPHERE/compute_temp_asphere.cpp \
../lammps-dev/src/ASPHERE/fix_nh_asphere.cpp \
../lammps-dev/src/ASPHERE/fix_nph_asphere.cpp \
../lammps-dev/src/ASPHERE/fix_npt_asphere.cpp \
../lammps-dev/src/ASPHERE/fix_nve_asphere.cpp \
../lammps-dev/src/ASPHERE/fix_nve_asphere_noforce.cpp \
../lammps-dev/src/ASPHERE/fix_nve_line.cpp \
../lammps-dev/src/ASPHERE/fix_nve_tri.cpp \
../lammps-dev/src/ASPHERE/fix_nvt_asphere.cpp \
../lammps-dev/src/ASPHERE/pair_gayberne.cpp \
../lammps-dev/src/ASPHERE/pair_line_lj.cpp \
../lammps-dev/src/ASPHERE/pair_resquared.cpp \
../lammps-dev/src/ASPHERE/pair_tri_lj.cpp 

OBJS += \
./lammps-dev/src/ASPHERE/compute_erotate_asphere.o \
./lammps-dev/src/ASPHERE/compute_temp_asphere.o \
./lammps-dev/src/ASPHERE/fix_nh_asphere.o \
./lammps-dev/src/ASPHERE/fix_nph_asphere.o \
./lammps-dev/src/ASPHERE/fix_npt_asphere.o \
./lammps-dev/src/ASPHERE/fix_nve_asphere.o \
./lammps-dev/src/ASPHERE/fix_nve_asphere_noforce.o \
./lammps-dev/src/ASPHERE/fix_nve_line.o \
./lammps-dev/src/ASPHERE/fix_nve_tri.o \
./lammps-dev/src/ASPHERE/fix_nvt_asphere.o \
./lammps-dev/src/ASPHERE/pair_gayberne.o \
./lammps-dev/src/ASPHERE/pair_line_lj.o \
./lammps-dev/src/ASPHERE/pair_resquared.o \
./lammps-dev/src/ASPHERE/pair_tri_lj.o 

CPP_DEPS += \
./lammps-dev/src/ASPHERE/compute_erotate_asphere.d \
./lammps-dev/src/ASPHERE/compute_temp_asphere.d \
./lammps-dev/src/ASPHERE/fix_nh_asphere.d \
./lammps-dev/src/ASPHERE/fix_nph_asphere.d \
./lammps-dev/src/ASPHERE/fix_npt_asphere.d \
./lammps-dev/src/ASPHERE/fix_nve_asphere.d \
./lammps-dev/src/ASPHERE/fix_nve_asphere_noforce.d \
./lammps-dev/src/ASPHERE/fix_nve_line.d \
./lammps-dev/src/ASPHERE/fix_nve_tri.d \
./lammps-dev/src/ASPHERE/fix_nvt_asphere.d \
./lammps-dev/src/ASPHERE/pair_gayberne.d \
./lammps-dev/src/ASPHERE/pair_line_lj.d \
./lammps-dev/src/ASPHERE/pair_resquared.d \
./lammps-dev/src/ASPHERE/pair_tri_lj.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/ASPHERE/%.o: ../lammps-dev/src/ASPHERE/%.cpp lammps-dev/src/ASPHERE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


