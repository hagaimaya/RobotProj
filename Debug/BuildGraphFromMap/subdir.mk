################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BuildGraphFromMap/Astar.cpp \
../BuildGraphFromMap/Graph.cpp \
../BuildGraphFromMap/Location.cpp \
../BuildGraphFromMap/Map.cpp \
../BuildGraphFromMap/Node.cpp \
../BuildGraphFromMap/lodepng.cpp 

OBJS += \
./BuildGraphFromMap/Astar.o \
./BuildGraphFromMap/Graph.o \
./BuildGraphFromMap/Location.o \
./BuildGraphFromMap/Map.o \
./BuildGraphFromMap/Node.o \
./BuildGraphFromMap/lodepng.o 

CPP_DEPS += \
./BuildGraphFromMap/Astar.d \
./BuildGraphFromMap/Graph.d \
./BuildGraphFromMap/Location.d \
./BuildGraphFromMap/Map.d \
./BuildGraphFromMap/Node.d \
./BuildGraphFromMap/lodepng.d 


# Each subdirectory must supply rules for building sources it contributes
BuildGraphFromMap/%.o: ../BuildGraphFromMap/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


