################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/protocolbuffer/Ack.pb.cpp \
../src/protocolbuffer/ChatMsg.pb.cpp \
../src/protocolbuffer/Common.pb.cpp \
../src/protocolbuffer/GroupUserListGet.pb.cpp \
../src/protocolbuffer/GroupUserListGetAck.pb.cpp \
../src/protocolbuffer/MsgNotify.pb.cpp \
../src/protocolbuffer/MsgObject.pb.cpp \
../src/protocolbuffer/MsgSync.pb.cpp \
../src/protocolbuffer/UserLogin.pb.cpp \
../src/protocolbuffer/UserLoginAck.pb.cpp \
../src/protocolbuffer/UserLogout.pb.cpp 

CC_SRCS += \
../src/protocolbuffer/GroupUserListGet.pb.cc 

OBJS += \
./src/protocolbuffer/Ack.pb.o \
./src/protocolbuffer/ChatMsg.pb.o \
./src/protocolbuffer/Common.pb.o \
./src/protocolbuffer/GroupUserListGet.pb.o \
./src/protocolbuffer/GroupUserListGetAck.pb.o \
./src/protocolbuffer/MsgNotify.pb.o \
./src/protocolbuffer/MsgObject.pb.o \
./src/protocolbuffer/MsgSync.pb.o \
./src/protocolbuffer/UserLogin.pb.o \
./src/protocolbuffer/UserLoginAck.pb.o \
./src/protocolbuffer/UserLogout.pb.o 

CC_DEPS += \
./src/protocolbuffer/GroupUserListGet.pb.d 

CPP_DEPS += \
./src/protocolbuffer/Ack.pb.d \
./src/protocolbuffer/ChatMsg.pb.d \
./src/protocolbuffer/Common.pb.d \
./src/protocolbuffer/GroupUserListGet.pb.d \
./src/protocolbuffer/GroupUserListGetAck.pb.d \
./src/protocolbuffer/MsgNotify.pb.d \
./src/protocolbuffer/MsgObject.pb.d \
./src/protocolbuffer/MsgSync.pb.d \
./src/protocolbuffer/UserLogin.pb.d \
./src/protocolbuffer/UserLoginAck.pb.d \
./src/protocolbuffer/UserLogout.pb.d 


# Each subdirectory must supply rules for building sources it contributes
src/protocolbuffer/%.o: ../src/protocolbuffer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/protocolbuffer/%.o: ../src/protocolbuffer/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


