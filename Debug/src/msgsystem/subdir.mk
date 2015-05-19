################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/msgsystem/Config.cpp \
../src/msgsystem/ModuleMgr.cpp \
../src/msgsystem/MsgSystemSvr.cpp \
../src/msgsystem/SvrFrame.cpp \
../src/msgsystem/TestCase.cpp 

OBJS += \
./src/msgsystem/Config.o \
./src/msgsystem/ModuleMgr.o \
./src/msgsystem/MsgSystemSvr.o \
./src/msgsystem/SvrFrame.o \
./src/msgsystem/TestCase.o 

CPP_DEPS += \
./src/msgsystem/Config.d \
./src/msgsystem/ModuleMgr.d \
./src/msgsystem/MsgSystemSvr.d \
./src/msgsystem/SvrFrame.d \
./src/msgsystem/TestCase.d 


# Each subdirectory must supply rules for building sources it contributes
src/msgsystem/%.o: ../src/msgsystem/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


