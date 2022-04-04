################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EminEmaxFinder.cpp \
../src/FileManager.cpp \
../src/KPM.cpp \
../src/KPMParameters.cpp \
../src/main.cpp 

O_SRCS += \
../src/FileManager.o \
../src/KPM.o \
../src/emin.o \
../src/main.o 

OBJS += \
./src/EminEmaxFinder.o \
./src/FileManager.o \
./src/KPM.o \
./src/KPMParameters.o \
./src/main.o 

CPP_DEPS += \
./src/EminEmaxFinder.d \
./src/FileManager.d \
./src/KPM.d \
./src/KPMParameters.d \
./src/main.d 
# Each subdirectory must supply rules for building sources it contributes
include src/includes.mk
src/%.o: ../src/%.cpp src/subdir.mk src/includes.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I../include -I/usr/include -I$(spectradir) -I$(mpichdir) -I$(boostinclude) -I$(eigendir) -O3 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


