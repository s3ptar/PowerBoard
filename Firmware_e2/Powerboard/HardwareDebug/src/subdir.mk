################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Powerboard.c \
../src/board.c 

C_DEPS += \
./src/Powerboard.d \
./src/board.d 

OBJS += \
./src/Powerboard.o \
./src/board.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=100 -mcpu=rx600 -misa=v1 -mlittle-endian-data -nostdinc -I"C:/projekte/Repo/Powerboard/Firmware_e2/Powerboard/generate" -I"C:\\Program Files (x86)\\GCC for Renesas RX 4.8.4.201803-GNURX-ELF\\rx-elf\\rx-elf\\/rx-elf/optlibinc" -DCPPAPP -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@")
	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


