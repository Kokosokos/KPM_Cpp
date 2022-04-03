################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../utests/gtest_main.cpp \
../utests/test.cpp 

OBJS += \
./utests/gtest_main.o \
./utests/test.o 

CPP_DEPS += \
./utests/gtest_main.d \
./utests/test.d 


# Each subdirectory must supply rules for building sources it contributes
utests/%.o: ../utests/%.cpp utests/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O3 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


