################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Localization/LocalizationManager.cpp \
../Localization/Particle.cpp 

OBJS += \
./Localization/LocalizationManager.o \
./Localization/Particle.o 

CPP_DEPS += \
./Localization/LocalizationManager.d \
./Localization/Particle.d 


# Each subdirectory must supply rules for building sources it contributes
Localization/%.o: ../Localization/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


