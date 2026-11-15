# UFO

A spinning-cube scene and a blur routine from a DOS demo project. [CUBEPART.CPP](CUBEPART.CPP) sets up the scene and loads a bitmap used for shading the cubes.

[BLUR.CPP](BLUR.CPP#L5) is a small Watcom x86 loop. It adds four neighbors from a 320-pixel-wide buffer and shifts right by two to get their average. `ESI` and `EDI` walk the input and output one byte at a time.

These are scene sources. The original EOS dependencies and demo assets are needed to build the scene.
