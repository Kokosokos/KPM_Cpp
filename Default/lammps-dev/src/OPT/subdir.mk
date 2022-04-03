################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/OPT/pair_eam_alloy_opt.cpp \
../lammps-dev/src/OPT/pair_eam_fs_opt.cpp \
../lammps-dev/src/OPT/pair_eam_opt.cpp \
../lammps-dev/src/OPT/pair_lj_charmm_coul_long_opt.cpp \
../lammps-dev/src/OPT/pair_lj_cut_coul_long_opt.cpp \
../lammps-dev/src/OPT/pair_lj_cut_opt.cpp \
../lammps-dev/src/OPT/pair_lj_cut_tip4p_long_opt.cpp \
../lammps-dev/src/OPT/pair_lj_long_coul_long_opt.cpp \
../lammps-dev/src/OPT/pair_morse_opt.cpp \
../lammps-dev/src/OPT/pair_ufm_opt.cpp 

OBJS += \
./lammps-dev/src/OPT/pair_eam_alloy_opt.o \
./lammps-dev/src/OPT/pair_eam_fs_opt.o \
./lammps-dev/src/OPT/pair_eam_opt.o \
./lammps-dev/src/OPT/pair_lj_charmm_coul_long_opt.o \
./lammps-dev/src/OPT/pair_lj_cut_coul_long_opt.o \
./lammps-dev/src/OPT/pair_lj_cut_opt.o \
./lammps-dev/src/OPT/pair_lj_cut_tip4p_long_opt.o \
./lammps-dev/src/OPT/pair_lj_long_coul_long_opt.o \
./lammps-dev/src/OPT/pair_morse_opt.o \
./lammps-dev/src/OPT/pair_ufm_opt.o 

CPP_DEPS += \
./lammps-dev/src/OPT/pair_eam_alloy_opt.d \
./lammps-dev/src/OPT/pair_eam_fs_opt.d \
./lammps-dev/src/OPT/pair_eam_opt.d \
./lammps-dev/src/OPT/pair_lj_charmm_coul_long_opt.d \
./lammps-dev/src/OPT/pair_lj_cut_coul_long_opt.d \
./lammps-dev/src/OPT/pair_lj_cut_opt.d \
./lammps-dev/src/OPT/pair_lj_cut_tip4p_long_opt.d \
./lammps-dev/src/OPT/pair_lj_long_coul_long_opt.d \
./lammps-dev/src/OPT/pair_morse_opt.d \
./lammps-dev/src/OPT/pair_ufm_opt.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/OPT/%.o: ../lammps-dev/src/OPT/%.cpp lammps-dev/src/OPT/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


