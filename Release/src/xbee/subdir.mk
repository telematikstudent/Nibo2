################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/xbee/niboCom.c \
../src/xbee/uart0.c 

OBJS += \
./src/xbee/niboCom.o \
./src/xbee/uart0.o 

C_DEPS += \
./src/xbee/niboCom.d \
./src/xbee/uart0.d 


# Each subdirectory must supply rules for building sources it contributes
src/xbee/%.o: ../src/xbee/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


