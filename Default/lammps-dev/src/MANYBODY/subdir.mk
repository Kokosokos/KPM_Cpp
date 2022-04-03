################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/MANYBODY/fix_qeq_comb.cpp \
../lammps-dev/src/MANYBODY/pair_adp.cpp \
../lammps-dev/src/MANYBODY/pair_airebo.cpp \
../lammps-dev/src/MANYBODY/pair_airebo_morse.cpp \
../lammps-dev/src/MANYBODY/pair_atm.cpp \
../lammps-dev/src/MANYBODY/pair_bop.cpp \
../lammps-dev/src/MANYBODY/pair_comb.cpp \
../lammps-dev/src/MANYBODY/pair_comb3.cpp \
../lammps-dev/src/MANYBODY/pair_eam.cpp \
../lammps-dev/src/MANYBODY/pair_eam_alloy.cpp \
../lammps-dev/src/MANYBODY/pair_eam_cd.cpp \
../lammps-dev/src/MANYBODY/pair_eam_fs.cpp \
../lammps-dev/src/MANYBODY/pair_eam_he.cpp \
../lammps-dev/src/MANYBODY/pair_eim.cpp \
../lammps-dev/src/MANYBODY/pair_gw.cpp \
../lammps-dev/src/MANYBODY/pair_gw_zbl.cpp \
../lammps-dev/src/MANYBODY/pair_lcbop.cpp \
../lammps-dev/src/MANYBODY/pair_nb3b_harmonic.cpp \
../lammps-dev/src/MANYBODY/pair_polymorphic.cpp \
../lammps-dev/src/MANYBODY/pair_rebo.cpp \
../lammps-dev/src/MANYBODY/pair_sw.cpp \
../lammps-dev/src/MANYBODY/pair_tersoff.cpp \
../lammps-dev/src/MANYBODY/pair_tersoff_mod.cpp \
../lammps-dev/src/MANYBODY/pair_tersoff_mod_c.cpp \
../lammps-dev/src/MANYBODY/pair_tersoff_zbl.cpp \
../lammps-dev/src/MANYBODY/pair_vashishta.cpp \
../lammps-dev/src/MANYBODY/pair_vashishta_table.cpp 

OBJS += \
./lammps-dev/src/MANYBODY/fix_qeq_comb.o \
./lammps-dev/src/MANYBODY/pair_adp.o \
./lammps-dev/src/MANYBODY/pair_airebo.o \
./lammps-dev/src/MANYBODY/pair_airebo_morse.o \
./lammps-dev/src/MANYBODY/pair_atm.o \
./lammps-dev/src/MANYBODY/pair_bop.o \
./lammps-dev/src/MANYBODY/pair_comb.o \
./lammps-dev/src/MANYBODY/pair_comb3.o \
./lammps-dev/src/MANYBODY/pair_eam.o \
./lammps-dev/src/MANYBODY/pair_eam_alloy.o \
./lammps-dev/src/MANYBODY/pair_eam_cd.o \
./lammps-dev/src/MANYBODY/pair_eam_fs.o \
./lammps-dev/src/MANYBODY/pair_eam_he.o \
./lammps-dev/src/MANYBODY/pair_eim.o \
./lammps-dev/src/MANYBODY/pair_gw.o \
./lammps-dev/src/MANYBODY/pair_gw_zbl.o \
./lammps-dev/src/MANYBODY/pair_lcbop.o \
./lammps-dev/src/MANYBODY/pair_nb3b_harmonic.o \
./lammps-dev/src/MANYBODY/pair_polymorphic.o \
./lammps-dev/src/MANYBODY/pair_rebo.o \
./lammps-dev/src/MANYBODY/pair_sw.o \
./lammps-dev/src/MANYBODY/pair_tersoff.o \
./lammps-dev/src/MANYBODY/pair_tersoff_mod.o \
./lammps-dev/src/MANYBODY/pair_tersoff_mod_c.o \
./lammps-dev/src/MANYBODY/pair_tersoff_zbl.o \
./lammps-dev/src/MANYBODY/pair_vashishta.o \
./lammps-dev/src/MANYBODY/pair_vashishta_table.o 

CPP_DEPS += \
./lammps-dev/src/MANYBODY/fix_qeq_comb.d \
./lammps-dev/src/MANYBODY/pair_adp.d \
./lammps-dev/src/MANYBODY/pair_airebo.d \
./lammps-dev/src/MANYBODY/pair_airebo_morse.d \
./lammps-dev/src/MANYBODY/pair_atm.d \
./lammps-dev/src/MANYBODY/pair_bop.d \
./lammps-dev/src/MANYBODY/pair_comb.d \
./lammps-dev/src/MANYBODY/pair_comb3.d \
./lammps-dev/src/MANYBODY/pair_eam.d \
./lammps-dev/src/MANYBODY/pair_eam_alloy.d \
./lammps-dev/src/MANYBODY/pair_eam_cd.d \
./lammps-dev/src/MANYBODY/pair_eam_fs.d \
./lammps-dev/src/MANYBODY/pair_eam_he.d \
./lammps-dev/src/MANYBODY/pair_eim.d \
./lammps-dev/src/MANYBODY/pair_gw.d \
./lammps-dev/src/MANYBODY/pair_gw_zbl.d \
./lammps-dev/src/MANYBODY/pair_lcbop.d \
./lammps-dev/src/MANYBODY/pair_nb3b_harmonic.d \
./lammps-dev/src/MANYBODY/pair_polymorphic.d \
./lammps-dev/src/MANYBODY/pair_rebo.d \
./lammps-dev/src/MANYBODY/pair_sw.d \
./lammps-dev/src/MANYBODY/pair_tersoff.d \
./lammps-dev/src/MANYBODY/pair_tersoff_mod.d \
./lammps-dev/src/MANYBODY/pair_tersoff_mod_c.d \
./lammps-dev/src/MANYBODY/pair_tersoff_zbl.d \
./lammps-dev/src/MANYBODY/pair_vashishta.d \
./lammps-dev/src/MANYBODY/pair_vashishta_table.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/MANYBODY/%.o: ../lammps-dev/src/MANYBODY/%.cpp lammps-dev/src/MANYBODY/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


