################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/COMPRESS/dump_atom_gz.cpp \
../lammps-dev/src/COMPRESS/dump_atom_zstd.cpp \
../lammps-dev/src/COMPRESS/dump_cfg_gz.cpp \
../lammps-dev/src/COMPRESS/dump_cfg_zstd.cpp \
../lammps-dev/src/COMPRESS/dump_custom_gz.cpp \
../lammps-dev/src/COMPRESS/dump_custom_zstd.cpp \
../lammps-dev/src/COMPRESS/dump_local_gz.cpp \
../lammps-dev/src/COMPRESS/dump_local_zstd.cpp \
../lammps-dev/src/COMPRESS/dump_xyz_gz.cpp \
../lammps-dev/src/COMPRESS/dump_xyz_zstd.cpp \
../lammps-dev/src/COMPRESS/zstd_file_writer.cpp 

OBJS += \
./lammps-dev/src/COMPRESS/dump_atom_gz.o \
./lammps-dev/src/COMPRESS/dump_atom_zstd.o \
./lammps-dev/src/COMPRESS/dump_cfg_gz.o \
./lammps-dev/src/COMPRESS/dump_cfg_zstd.o \
./lammps-dev/src/COMPRESS/dump_custom_gz.o \
./lammps-dev/src/COMPRESS/dump_custom_zstd.o \
./lammps-dev/src/COMPRESS/dump_local_gz.o \
./lammps-dev/src/COMPRESS/dump_local_zstd.o \
./lammps-dev/src/COMPRESS/dump_xyz_gz.o \
./lammps-dev/src/COMPRESS/dump_xyz_zstd.o \
./lammps-dev/src/COMPRESS/zstd_file_writer.o 

CPP_DEPS += \
./lammps-dev/src/COMPRESS/dump_atom_gz.d \
./lammps-dev/src/COMPRESS/dump_atom_zstd.d \
./lammps-dev/src/COMPRESS/dump_cfg_gz.d \
./lammps-dev/src/COMPRESS/dump_cfg_zstd.d \
./lammps-dev/src/COMPRESS/dump_custom_gz.d \
./lammps-dev/src/COMPRESS/dump_custom_zstd.d \
./lammps-dev/src/COMPRESS/dump_local_gz.d \
./lammps-dev/src/COMPRESS/dump_local_zstd.d \
./lammps-dev/src/COMPRESS/dump_xyz_gz.d \
./lammps-dev/src/COMPRESS/dump_xyz_zstd.d \
./lammps-dev/src/COMPRESS/zstd_file_writer.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/COMPRESS/%.o: ../lammps-dev/src/COMPRESS/%.cpp lammps-dev/src/COMPRESS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


