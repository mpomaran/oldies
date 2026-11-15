# Onyx v2

My DOS software renderer. It uses VESA for the display and draws textured triangles with Gouraud shading, clipping and a Z-buffer. [CUBES.CPP](EXAMPLES/CUBES/CUBES.CPP) draws two spinning cubes and is a good place to start.

- [SOURCE/VIDEO](SOURCE/VIDEO/) has the triangle rasterizers and framebuffer.
- [SOURCE/LOW-LEV](SOURCE/LOW-LEV/) talks to VESA and handles real-mode interrupts.
- [SOURCE/ENGINE3D](SOURCE/ENGINE3D/) handles objects and scenes. [TOOLS](TOOLS/) has the format converters.

This is the freeware beta from `onyx.zip`. [BUILD.BAT](BUILD.BAT) uses Watcom tools. It expects a `LIB` directory, and some examples need EOS or their original data files.

[Onyx on Direct3D 8](../onyx/) is the later Windows experiment.
