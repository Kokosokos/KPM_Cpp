################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/src/KIM/fix_store_kim.cpp \
../lammps-dev/src/KIM/kim_command.cpp \
../lammps-dev/src/KIM/kim_init.cpp \
../lammps-dev/src/KIM/kim_interactions.cpp \
../lammps-dev/src/KIM/kim_param.cpp \
../lammps-dev/src/KIM/kim_property.cpp \
../lammps-dev/src/KIM/kim_query.cpp \
../lammps-dev/src/KIM/kim_units.cpp \
../lammps-dev/src/KIM/pair_kim.cpp 

OBJS += \
./lammps-dev/src/KIM/fix_store_kim.o \
./lammps-dev/src/KIM/kim_command.o \
./lammps-dev/src/KIM/kim_init.o \
./lammps-dev/src/KIM/kim_interactions.o \
./lammps-dev/src/KIM/kim_param.o \
./lammps-dev/src/KIM/kim_property.o \
./lammps-dev/src/KIM/kim_query.o \
./lammps-dev/src/KIM/kim_units.o \
./lammps-dev/src/KIM/pair_kim.o 

CPP_DEPS += \
./lammps-dev/src/KIM/fix_store_kim.d \
./lammps-dev/src/KIM/kim_command.d \
./lammps-dev/src/KIM/kim_init.d \
./lammps-dev/src/KIM/kim_interactions.d \
./lammps-dev/src/KIM/kim_param.d \
./lammps-dev/src/KIM/kim_property.d \
./lammps-dev/src/KIM/kim_query.d \
./lammps-dev/src/KIM/kim_units.d \
./lammps-dev/src/KIM/pair_kim.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/src/KIM/%.o: ../lammps-dev/src/KIM/%.cpp lammps-dev/src/KIM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


