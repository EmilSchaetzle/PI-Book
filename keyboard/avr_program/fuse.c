#include <avr/io.h>
// Set Fuses with "avrdude -C"$(PROJECTDIR)avrdude.conf" -v -p m2560 -c avrisp -P /dev/ttyACM0 -b 19200  -U efuse:w:0xFD:m"
// Upload to board with "avrdude -C"$(PROJECTDIR)avrdude.conf" -v -p m2560 -c avrisp -P /dev/ttyACM0 -b 19200 -Uflash:w:"$(PROJECTDIR)bin/Release/avr_program.hex":i"
FUSES =
{
    .low = 0x5C,
    .high = 0xD9,
    .extended = 0xFF
};
