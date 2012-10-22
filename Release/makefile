################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
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

EEPROM_IMAGE += \
defaultCProject.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: defaultCProject.elf secondary-outputs

# Tool invocations
defaultCProject.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,defaultCProject.map -mmcu=atmega128 -o"defaultCProject.elf" $(OBJS) $(USER_OBJS) $(LIBS)
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

defaultCProject.eep: defaultCProject.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex defaultCProject.elf  "defaultCProject.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: defaultCProject.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t defaultCProject.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) defaultCProject.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
