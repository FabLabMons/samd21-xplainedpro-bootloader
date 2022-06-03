BOOTLOADER_OBJS += $(OBJS)
BOOTLOADER_OBJS += \
bootloader.o

BOOTLOADER_OBJS_AS_ARGS +=  $(OBJS_AS_ARGS)
BOOTLOADER_OBJS_AS_ARGS +=  \
"bootloader.o"

bootloader.elf: $(BOOTLOADER_OBJS)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker
	$(QUOTE)arm-none-eabi-gcc$(QUOTE) -o bootloader.elf $(BOOTLOADER_OBJS_AS_ARGS) -Wl,--start-group -lm -Wl,--end-group -mthumb \
-Wl,-Map="bootloader.map" --specs=nano.specs -Wl,--gc-sections -mcpu=cortex-m0plus \
 \
-T"../samd21a/gcc/gcc/bootloader.ld" \
-L"../samd21a/gcc/gcc"
	@echo Finished building target: $@

	"arm-none-eabi-objcopy" --pad-to=0x4000 --gap-fill=0xFF -O binary "bootloader.elf" "bootloader.bin"
	"arm-none-eabi-objcopy" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  \
        "bootloader.elf" "bootloader.hex"
	"arm-none-eabi-objcopy" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma \
        .eeprom=0 --no-change-warnings -O binary "bootloader.elf" \
        "bootloader.eep" || exit 0
	"arm-none-eabi-objdump" -h -S "bootloader.elf" > "bootloader.lss"
	"arm-none-eabi-size" "bootloader.elf"