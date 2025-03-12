################################################################################
# MRS Version: 1.9.2
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
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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
oled_049_r4_CH32V003A4M6.hex \

SECONDARY_LIST += \
oled_049_r4_CH32V003A4M6.lst \

SECONDARY_SIZE += \
oled_049_r4_CH32V003A4M6.siz \


# All Target
all: oled_049_r4_CH32V003A4M6.elf secondary-outputs

# Tool invocations
oled_049_r4_CH32V003A4M6.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-elf-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\MRS_DATA\workspace\oled_049_r4_CH32V003A4M6\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"oled_049_r4_CH32V003A4M6.map" --specs=nano.specs --specs=nosys.specs -o "oled_049_r4_CH32V003A4M6.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintf
	@	@
oled_049_r4_CH32V003A4M6.hex: oled_049_r4_CH32V003A4M6.elf
	@	riscv-none-elf-objcopy -O ihex "oled_049_r4_CH32V003A4M6.elf"  "oled_049_r4_CH32V003A4M6.hex"
	@	@
oled_049_r4_CH32V003A4M6.lst: oled_049_r4_CH32V003A4M6.elf
	@	riscv-none-elf-objdump --all-headers --demangle --disassemble -M xw "oled_049_r4_CH32V003A4M6.elf" > "oled_049_r4_CH32V003A4M6.lst"
	@	@
oled_049_r4_CH32V003A4M6.siz: oled_049_r4_CH32V003A4M6.elf
	@	riscv-none-elf-size --format=berkeley "oled_049_r4_CH32V003A4M6.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) oled_049_r4_CH32V003A4M6.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
