################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lammps-dev/lib/colvars/lepton/src/CompiledExpression.cpp \
../lammps-dev/lib/colvars/lepton/src/ExpressionProgram.cpp \
../lammps-dev/lib/colvars/lepton/src/ExpressionTreeNode.cpp \
../lammps-dev/lib/colvars/lepton/src/Operation.cpp \
../lammps-dev/lib/colvars/lepton/src/ParsedExpression.cpp \
../lammps-dev/lib/colvars/lepton/src/Parser.cpp 

OBJS += \
./lammps-dev/lib/colvars/lepton/src/CompiledExpression.o \
./lammps-dev/lib/colvars/lepton/src/ExpressionProgram.o \
./lammps-dev/lib/colvars/lepton/src/ExpressionTreeNode.o \
./lammps-dev/lib/colvars/lepton/src/Operation.o \
./lammps-dev/lib/colvars/lepton/src/ParsedExpression.o \
./lammps-dev/lib/colvars/lepton/src/Parser.o 

CPP_DEPS += \
./lammps-dev/lib/colvars/lepton/src/CompiledExpression.d \
./lammps-dev/lib/colvars/lepton/src/ExpressionProgram.d \
./lammps-dev/lib/colvars/lepton/src/ExpressionTreeNode.d \
./lammps-dev/lib/colvars/lepton/src/Operation.d \
./lammps-dev/lib/colvars/lepton/src/ParsedExpression.d \
./lammps-dev/lib/colvars/lepton/src/Parser.d 


# Each subdirectory must supply rules for building sources it contributes
lammps-dev/lib/colvars/lepton/src/%.o: ../lammps-dev/lib/colvars/lepton/src/%.cpp lammps-dev/lib/colvars/lepton/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -I"/mnt/data/home/codes/eclipse-workdir/KPM_Cpp/include" -I/mnt/data/home/codes/libs/spectra/include -I/usr/include/x86_64-linux-gnu/mpich/ -I/usr/include -I/mnt/data/home/codes/libs/include -I/mnt/data/home/codes/libs/eigen-3.4.0 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


