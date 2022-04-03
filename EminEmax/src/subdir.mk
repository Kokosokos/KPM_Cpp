################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EminEmaxFinder.cpp \
../src/FileManager.cpp \
../src/KPM.cpp \
../src/eminemax.cpp 

O_SRCS += \
../src/FileManager.o \
../src/KPM.o \
../src/emin.o \
../src/main.o 

OBJS += \
./src/EminEmaxFinder.o \
./src/FileManager.o \
./src/KPM.o \
./src/eminemax.o 

CPP_DEPS += \
./src/EminEmaxFinder.d \
./src/FileManager.d \
./src/KPM.d \
./src/eminemax.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O3 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


