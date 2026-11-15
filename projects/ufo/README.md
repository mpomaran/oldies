# UFO

I worked on this DOS demo as Sarin/!ArisE!. There are spinning cubes, flashes, noise and a blur that smears the image across a 320×200 VGA screen.

[3DPART/3DTEST.CPP](3DPART/3DTEST.CPP) is the entry point for the cube test. [BLUR.CPP](BLUR.CPP#L5) has the Watcom x86 loop that adds four neighboring pixels and shifts right by two.

[DATA](DATA/) has the original GPH animations and fonts, raw images and tracker music, including [MUSIC.MOD](DATA/MUSIC.MOD) and [another file with the same name](DATA/MUSIC-ALT.MOD) from outside the RAR. The cube test has its own [BMP.RAW](3DPART/BMP.RAW).

The [makefile](3DPART/MAKEFILE) uses Watcom C++, EOS and the original 3D library.
