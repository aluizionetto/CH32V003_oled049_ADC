################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
oled_049_r1_CH32V003A4M6.hex \

SECONDARY_LIST += \
oled_049_r1_CH32V003A4M6.lst \

SECONDARY_SIZE += \
oled_049_r1_CH32V003A4M6.siz \


# All Target
all: oled_049_r1_CH32V003A4M6.elf secondary-outputs

# Tool invocations
oled_049_r1_CH32V003A4M6.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32ec -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\RISC-V\mrs_workspace\oled_049_r1_CH32V003A4M6\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"oled_049_r1_CH32V003A4M6.map" --specs=nano.specs --specs=nosys.specs -o "oled_049_r1_CH32V003A4M6.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

oled_049_r1_CH32V003A4M6.hex: oled_049_r1_CH32V003A4M6.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "oled_049_r1_CH32V003A4M6.elf"  "oled_049_r1_CH32V003A4M6.hex"
	@echo 'Finished building: $@'
	@echo ' '

oled_049_r1_CH32V003A4M6.lst: oled_049_r1_CH32V003A4M6.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --all-headers --demangle --disassemble "oled_049_r1_CH32V003A4M6.elf" > "oled_049_r1_CH32V003A4M6.lst"
	@echo 'Finished building: $@'
	@echo ' '

oled_049_r1_CH32V003A4M6.siz: oled_049_r1_CH32V003A4M6.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "oled_049_r1_CH32V003A4M6.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) oled_049_r1_CH32V003A4M6.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
