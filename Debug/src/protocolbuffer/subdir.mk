################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/protocolbuffer/Ack.pb.cpp \
../src/protocolbuffer/ActivityRoom.pb.cpp \
../src/protocolbuffer/ChatMsg.pb.cpp \
../src/protocolbuffer/Common.pb.cpp \
../src/protocolbuffer/GroupUserAdd.pb.cpp \
../src/protocolbuffer/GroupUserListAck.pb.cpp \
../src/protocolbuffer/GroupUserListRequest.pb.cpp \
../src/protocolbuffer/ModuleLogin.pb.cpp \
../src/protocolbuffer/ModuleLoginAck.pb.cpp \
../src/protocolbuffer/MsgNotify.pb.cpp \
../src/protocolbuffer/MsgObject.pb.cpp \
../src/protocolbuffer/MsgSync.pb.cpp \
../src/protocolbuffer/Push.pb.cpp \
../src/protocolbuffer/UserForceOffline.pb.cpp \
../src/protocolbuffer/UserLogin.pb.cpp \
../src/protocolbuffer/UserLoginAck.pb.cpp \
../src/protocolbuffer/UserLogout.pb.cpp 

OBJS += \
./src/protocolbuffer/Ack.pb.o \
./src/protocolbuffer/ActivityRoom.pb.o \
./src/protocolbuffer/ChatMsg.pb.o \
./src/protocolbuffer/Common.pb.o \
./src/protocolbuffer/GroupUserAdd.pb.o \
./src/protocolbuffer/GroupUserListAck.pb.o \
./src/protocolbuffer/GroupUserListRequest.pb.o \
./src/protocolbuffer/ModuleLogin.pb.o \
./src/protocolbuffer/ModuleLoginAck.pb.o \
./src/protocolbuffer/MsgNotify.pb.o \
./src/protocolbuffer/MsgObject.pb.o \
./src/protocolbuffer/MsgSync.pb.o \
./src/protocolbuffer/Push.pb.o \
./src/protocolbuffer/UserForceOffline.pb.o \
./src/protocolbuffer/UserLogin.pb.o \
./src/protocolbuffer/UserLoginAck.pb.o \
./src/protocolbuffer/UserLogout.pb.o 

CPP_DEPS += \
./src/protocolbuffer/Ack.pb.d \
./src/protocolbuffer/ActivityRoom.pb.d \
./src/protocolbuffer/ChatMsg.pb.d \
./src/protocolbuffer/Common.pb.d \
./src/protocolbuffer/GroupUserAdd.pb.d \
./src/protocolbuffer/GroupUserListAck.pb.d \
./src/protocolbuffer/GroupUserListRequest.pb.d \
./src/protocolbuffer/ModuleLogin.pb.d \
./src/protocolbuffer/ModuleLoginAck.pb.d \
./src/protocolbuffer/MsgNotify.pb.d \
./src/protocolbuffer/MsgObject.pb.d \
./src/protocolbuffer/MsgSync.pb.d \
./src/protocolbuffer/Push.pb.d \
./src/protocolbuffer/UserForceOffline.pb.d \
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


