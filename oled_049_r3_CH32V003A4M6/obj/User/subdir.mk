################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v00x_it.c \
../User/main.c \
../User/oled_049.c \
../User/system_ch32v00x.c 

OBJS += \
./User/ch32v00x_it.o \
./User/main.o \
./User/oled_049.o \
./User/system_ch32v00x.o 

C_DEPS += \
./User/ch32v00x_it.d \
./User/main.d \
./User/oled_049.d \
./User/system_ch32v00x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\RISC-V\mrs_workspace\oled_049_r3_CH32V003A4M6\Debug" -I"D:\RISC-V\mrs_workspace\oled_049_r3_CH32V003A4M6\Core" -I"D:\RISC-V\mrs_workspace\oled_049_r3_CH32V003A4M6\User" -I"D:\RISC-V\mrs_workspace\oled_049_r3_CH32V003A4M6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


