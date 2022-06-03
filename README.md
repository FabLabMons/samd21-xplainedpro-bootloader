# ATSAMD21J18 Bootloader

This project was written to demonstrate a simple bootloader implementation for the ATSAMD21 Xplained Pro Evaluation board.
At launch, the bootloader blinks to show it's executed, then it starts the main application.

The main application is simply a blinky, which toggles faster than the bootloader.
An interrupt handler is defined on the board's user button.

The project is built on top of the Atmel Start bootstraping application: https://start.atmel.com/

To program the microcontroller, we use the Atmel-ICE programmer on the DEBUG usb port of the board.
To be able to communicate with the board, the file `openocd.cfg` is needed.
The ARM toolchain needs to be installed to build the project.

# Links
* ATSAMD21 Evaluation board:
  * https://www.microchip.com/en-us/development-tool/ATSAMD21-XPRO
  * https://microchipdeveloper.com/boards:sam-d21-xpro
* ARM toolchain: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

# Integration in your project
1. Create a `memory_map.ld` file to lay out the memory blocks and define the memory block variables, put it in the same directory as other generated ld files
2. Add a file `memory_map.h` in the root directory, defining the memory sections variables used in `bootloader.c`
3. In the generated ld file used by the linker (ie. samd21j18a_flash.ld), remove the MEMORY definition and replace with `INCLUDE memory_map.ld`
4. If needed, adapt the memory block name to each section
5. Create a bootloader.ld file by copy-pasting the file from 2
6. In this file, adapt the memory block assigned to sections to match the bootloader's memory block name (ie. from `rom` to `bootrom`)
7. Create a makefile for the bootloader and include it in the main makefile (see makefiles for their structures, they are commented):
  * remove the main.c, main.o from OBJS and OBJS_AS_ARGS variables
  * add them to specific variables for APP and BOOTLOADER (see inside makefiles)

# Debugging
1. `make` should build binary|elf|etc files for both application and bootloader, and also a full binary image containing the bootloader and the application
2. start gdb without specifying the executable file: `arm-none-eabi-gdb -ie "target extended-remote localhost:3333"`
3. load bootloader.elf
4. load application.elf
5. add-symbol-file bootloader.elf
6. add-symbol-file application.elf

Then continue the debugging process
