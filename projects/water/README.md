# Water

A little DOS demo that drops ripples into a 320×200 VGA screen. [WATER.CPP](WATER.CPP) alternates between two height buffers, sums four neighbors, subtracts the previous height and damps the result. The current height offsets where each pixel samples the background image.

[MAIN.CPP](MAIN.CPP#L14) sets the VGA palette with Watcom inline x86 and switches video modes with BIOS interrupt `10h`. It sends the frame straight to `0xA0000`. The startup screen says `Sarin/!ArisE!`.

The original build uses Watcom C++ and EOS. The code is here. The GIFs, tracker modules and original executable stay with the backup.

## DOSBox-X clip

[Watch 20 seconds of Water](water-dosbox.mp4). This run uses the original DOS effect with a replacement checkerboard and a test MOD. The audio was recorded from the emulator while it played the module. Space starts the effect from the intro. Enter during the effect returns to DOS.
