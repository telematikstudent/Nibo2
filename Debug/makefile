################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/xbee/subdir.mk
-include src/sound/subdir.mk
-include src/nds3/subdir.mk
-include src/subdir.mk
-include src/drive/subdir.mk
-include src/display/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
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
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
defaultCProject.lss \

FLASH_IMAGE += \
defaultCProject.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: defaultCProject.elf secondary-outputs

# Tool invocations
defaultCProject.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,defaultCProject.map -Wl,-u,vfprintf -L/home/defaultuser/nibolib/lib -mmcu=atmega128 -o"defaultCProject.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

defaultCProject.lss: defaultCProject.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S defaultCProject.elf  >"defaultCProject.lss"
	@echo 'Finished building: $@'
	@echo ' '

defaultCProject.hex: defaultCProject.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex defaultCProject.elf  "defaultCProject.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: defaultCProject.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t defaultCProject.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) defaultCProject.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
