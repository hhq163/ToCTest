################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/protocol/CCSGroupUserAdd.cpp \
../src/protocol/CCSGroupUserListAck.cpp \
../src/protocol/CCSGroupUserListRequest.cpp \
../src/protocol/CChatMsgRecv.cpp \
../src/protocol/CChatMsgSend.cpp \
../src/protocol/CGroupUserChange.cpp \
../src/protocol/CMsgActivityRoom.cpp \
../src/protocol/CMsgBase.cpp \
../src/protocol/CMsgBaseAck.cpp \
../src/protocol/CMsgForceOffline.cpp \
../src/protocol/CMsgHeartbeat.cpp \
../src/protocol/CMsgHeartbeatAck.cpp \
../src/protocol/CMsgModuleLogin.cpp \
../src/protocol/CMsgModuleLoginAck.cpp \
../src/protocol/CMsgNotify.cpp \
../src/protocol/CMsgNotifyAck.cpp \
../src/protocol/CMsgPush.cpp \
../src/protocol/CMsgSync.cpp \
../src/protocol/CMsgUserLogin.cpp \
../src/protocol/CMsgUserLoginAck.cpp \
../src/protocol/CMsgUserLogout.cpp \
../src/protocol/CRoomMsg.cpp 

OBJS += \
./src/protocol/CCSGroupUserAdd.o \
./src/protocol/CCSGroupUserListAck.o \
./src/protocol/CCSGroupUserListRequest.o \
./src/protocol/CChatMsgRecv.o \
./src/protocol/CChatMsgSend.o \
./src/protocol/CGroupUserChange.o \
./src/protocol/CMsgActivityRoom.o \
./src/protocol/CMsgBase.o \
./src/protocol/CMsgBaseAck.o \
./src/protocol/CMsgForceOffline.o \
./src/protocol/CMsgHeartbeat.o \
./src/protocol/CMsgHeartbeatAck.o \
./src/protocol/CMsgModuleLogin.o \
./src/protocol/CMsgModuleLoginAck.o \
./src/protocol/CMsgNotify.o \
./src/protocol/CMsgNotifyAck.o \
./src/protocol/CMsgPush.o \
./src/protocol/CMsgSync.o \
./src/protocol/CMsgUserLogin.o \
./src/protocol/CMsgUserLoginAck.o \
./src/protocol/CMsgUserLogout.o \
./src/protocol/CRoomMsg.o 

CPP_DEPS += \
./src/protocol/CCSGroupUserAdd.d \
./src/protocol/CCSGroupUserListAck.d \
./src/protocol/CCSGroupUserListRequest.d \
./src/protocol/CChatMsgRecv.d \
./src/protocol/CChatMsgSend.d \
./src/protocol/CGroupUserChange.d \
./src/protocol/CMsgActivityRoom.d \
./src/protocol/CMsgBase.d \
./src/protocol/CMsgBaseAck.d \
./src/protocol/CMsgForceOffline.d \
./src/protocol/CMsgHeartbeat.d \
./src/protocol/CMsgHeartbeatAck.d \
./src/protocol/CMsgModuleLogin.d \
./src/protocol/CMsgModuleLoginAck.d \
./src/protocol/CMsgNotify.d \
./src/protocol/CMsgNotifyAck.d \
./src/protocol/CMsgPush.d \
./src/protocol/CMsgSync.d \
./src/protocol/CMsgUserLogin.d \
./src/protocol/CMsgUserLoginAck.d \
./src/protocol/CMsgUserLogout.d \
./src/protocol/CRoomMsg.d 


# Each subdirectory must supply rules for building sources it contributes
src/protocol/%.o: ../src/protocol/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


