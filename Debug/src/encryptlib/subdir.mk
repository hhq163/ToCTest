################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/encryptlib/base64.c \
../src/encryptlib/padlock.c \
../src/encryptlib/vsha256.c 

OBJS += \
./src/encryptlib/base64.o \
./src/encryptlib/padlock.o \
./src/encryptlib/vsha256.o 

C_DEPS += \
./src/encryptlib/base64.d \
./src/encryptlib/padlock.d \
./src/encryptlib/vsha256.d 


# Each subdirectory must supply rules for building sources it contributes
src/encryptlib/%.o: ../src/encryptlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


