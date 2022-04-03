################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/colvars/colvar.cpp \
../lammps-dev/lib/colvars/colvaratoms.cpp \
../lammps-dev/lib/colvars/colvarbias.cpp \
../lammps-dev/lib/colvars/colvarbias_abf.cpp \
../lammps-dev/lib/colvars/colvarbias_alb.cpp \
../lammps-dev/lib/colvars/colvarbias_histogram.cpp \
../lammps-dev/lib/colvars/colvarbias_meta.cpp \
../lammps-dev/lib/colvars/colvarbias_restraint.cpp \
../lammps-dev/lib/colvars/colvarcomp.cpp \
../lammps-dev/lib/colvars/colvarcomp_angles.cpp \
../lammps-dev/lib/colvars/colvarcomp_apath.cpp \
../lammps-dev/lib/colvars/colvarcomp_coordnums.cpp \
../lammps-dev/lib/colvars/colvarcomp_distances.cpp \
../lammps-dev/lib/colvars/colvarcomp_gpath.cpp \
../lammps-dev/lib/colvars/colvarcomp_protein.cpp \
../lammps-dev/lib/colvars/colvarcomp_rotations.cpp \
../lammps-dev/lib/colvars/colvardeps.cpp \
../lammps-dev/lib/colvars/colvargrid.cpp \
../lammps-dev/lib/colvars/colvarmodule.cpp \
../lammps-dev/lib/colvars/colvarparams.cpp \
../lammps-dev/lib/colvars/colvarparse.cpp \
../lammps-dev/lib/colvars/colvarproxy.cpp \
../lammps-dev/lib/colvars/colvarproxy_replicas.cpp \
../lammps-dev/lib/colvars/colvarscript.cpp \
../lammps-dev/lib/colvars/colvartypes.cpp \
../lammps-dev/lib/colvars/colvarvalue.cpp 

OBJS += \
./lammps-dev/lib/colvars/colvar.o \
./lammps-dev/lib/colvars/colvaratoms.o \
./lammps-dev/lib/colvars/colvarbias.o \
./lammps-dev/lib/colvars/colvarbias_abf.o \
./lammps-dev/lib/colvars/colvarbias_alb.o \
./lammps-dev/lib/colvars/colvarbias_histogram.o \
./lammps-dev/lib/colvars/colvarbias_meta.o \
./lammps-dev/lib/colvars/colvarbias_restraint.o \
./lammps-dev/lib/colvars/colvarcomp.o \
./lammps-dev/lib/colvars/colvarcomp_angles.o \
./lammps-dev/lib/colvars/colvarcomp_apath.o \
./lammps-dev/lib/colvars/colvarcomp_coordnums.o \
./lammps-dev/lib/colvars/colvarcomp_distances.o \
./lammps-dev/lib/colvars/colvarcomp_gpath.o \
./lammps-dev/lib/colvars/colvarcomp_protein.o \
./lammps-dev/lib/colvars/colvarcomp_rotations.o \
./lammps-dev/lib/colvars/colvardeps.o \
./lammps-dev/lib/colvars/colvargrid.o \
./lammps-dev/lib/colvars/colvarmodule.o \
./lammps-dev/lib/colvars/colvarparams.o \
./lammps-dev/lib/colvars/colvarparse.o \
./lammps-dev/lib/colvars/colvarproxy.o \
./lammps-dev/lib/colvars/colvarproxy_replicas.o \
./lammps-dev/lib/colvars/colvarscript.o \
./lammps-dev/lib/colvars/colvartypes.o \
./lammps-dev/lib/colvars/colvarvalue.o 

CPP_DEPS += \
./lammps-dev/lib/colvars/colvar.d \
./lammps-dev/lib/colvars/colvaratoms.d \
./lammps-dev/lib/colvars/colvarbias.d \
./lammps-dev/lib/colvars/colvarbias_abf.d \
./lammps-dev/lib/colvars/colvarbias_alb.d \
./lammps-dev/lib/colvars/colvarbias_histogram.d \
./lammps-dev/lib/colvars/colvarbias_meta.d \
./lammps-dev/lib/colvars/colvarbias_restraint.d \
./lammps-dev/lib/colvars/colvarcomp.d \
./lammps-dev/lib/colvars/colvarcomp_angles.d \
./lammps-dev/lib/colvars/colvarcomp_apath.d \
./lammps-dev/lib/colvars/colvarcomp_coordnums.d \
./lammps-dev/lib/colvars/colvarcomp_distances.d \
./lammps-dev/lib/colvars/colvarcomp_gpath.d \
./lammps-dev/lib/colvars/colvarcomp_protein.d \
./lammps-dev/lib/colvars/colvarcomp_rotations.d \
./lammps-dev/lib/colvars/colvardeps.d \
./lammps-dev/lib/colvars/colvargrid.d \
./lammps-dev/lib/colvars/colvarmodule.d \
./lammps-dev/lib/colvars/colvarparams.d \
./lammps-dev/lib/colvars/colvarparse.d \
./lammps-dev/lib/colvars/colvarproxy.d \
./lammps-dev/lib/colvars/colvarproxy_replicas.d \
./lammps-dev/lib/colvars/colvarscript.d \
./lammps-dev/lib/colvars/colvartypes.d \
./lammps-dev/lib/colvars/colvarvalue.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/colvars/%.o: ../lammps-dev/lib/colvars/%.cpp lammps-dev/lib/colvars/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


