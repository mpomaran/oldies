# Water

A little DOS demo that drops ripples into a 320×200 VGA screen. [WATER.CPP](WATER.CPP) alternates between two height buffers, sums four neighbors, subtracts the previous height and damps the result. The current height offsets where each pixel samples the background image.

[MAIN.CPP](MAIN.CPP#L14) sets the VGA palette with Watcom inline x86 and switches video modes with BIOS interrupt `10h`. It sends the frame straight to `0xA0000`. The startup screen says `Sarin/!ArisE!`.

The original build uses Watcom C++ and EOS. The code is here. The GIFs, tracker modules and original executable stay with the backup.

## DOSBox-X clip

[Watch Water](water-dosbox.mp4). The DOS effect runs over a checkerboard with the music from the backup. The sound comes straight from DOSBox-X. Space starts the effect from the intro. Enter during the effect returns to DOS.
