################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/comm/Log.cpp \
../src/comm/Util.cpp 

OBJS += \
./src/comm/Log.o \
./src/comm/Util.o 

CPP_DEPS += \
./src/comm/Log.d \
./src/comm/Util.d 


# Each subdirectory must supply rules for building sources it contributes
src/comm/%.o: ../src/comm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


