################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LINKER_SCRIPT += \
../generate/linker_script.ld 

S_UPPER_SRCS += \
../generate/start.S 

C_SRCS += \
../generate/hwinit.c \
../generate/inthandler.c \
../generate/vects.c 

C_DEPS += \
./generate/hwinit.d \
./generate/inthandler.d \
./generate/vects.d 

OBJS += \
./generate/hwinit.o \
./generate/inthandler.o \
./generate/start.o \
./generate/vects.o 

S_UPPER_DEPS += \
./generate/start.d 


# Each subdirectory must supply rules for building sources it contributes
generate/%.o: ../generate/%.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=100 -mcpu=rx600 -misa=v1 -mlittle-endian-data -nostdinc -I"C:/projekte/Software/renesas/Powerboard/generate" -I"C:\\Program Files (x86)\\GCC for Renesas RX 4.8.4.201803-GNURX-ELF\\rx-elf\\rx-elf\\/rx-elf/optlibinc" -DCPPAPP -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@")
	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

generate/%.o: ../generate/%.S
	@echo 'Building file: $<'
	@echo 'Invoking Assembler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=100 -mcpu=rx600 -misa=v1 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -DCPPAPP -I"C:/projekte/Software/renesas/Powerboard/src" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@")
	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


