#! /bin/bash
arm-none-eabi-objcopy -O binary -S build/freewheel_25.elf build/freewheel_25.bin
CubeProgrammer -c port=SWD -w build/freewheel_25.bin 0x8000000 -c port=SWD reset=SWrst
