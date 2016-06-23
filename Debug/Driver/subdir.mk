################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Driver/Driver.cpp \
../Driver/Main1.cpp \
../Driver/Robot.cpp 

OBJS += \
./Driver/Driver.o \
./Driver/Main1.o \
./Driver/Robot.o 

CPP_DEPS += \
./Driver/Driver.d \
./Driver/Main1.d \
./Driver/Robot.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/%.o: ../Driver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


