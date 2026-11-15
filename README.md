# Early software archive

Selected C and C++ projects recovered from Michał Pomarański's April 2002 backup, alongside a small study archive.
The projects explore how data moves through software, from Huffman coding and object dispatch to height fields
and pixel buffers. [bf-radio](https://github.com/mpomaran/bf-radio) is a later C++ project on another part of
the same problem space: framing, synchronization and error correction for an audio modem.

Curated by **Michał Pomarański (Michal Pomaranski)** · [GitHub](https://github.com/mpomaran) · [LinkedIn](https://www.linkedin.com/in/michal-pomaranski/)

| Project | Focus |
| --- | --- |
| [CD player](projects/cdplayer/) | Win32 C++ experiment around CD playback |
| [Geometry engine](projects/engine/) | C++ geometry and 3D math snapshot |
| [Fractal terrain explorer](projects/fract01/) | Win32 GDI terrain demo with randomized height fields, a rectangular selection and a fractal-dimension command |
| [Fractal raster demo](projects/fractal/) | Win32 experiment generating a randomized height field and mapping it to grayscale with GDI `SetPixel` |
| [Adaptive Huffman coding](projects/huffman/) | 2001 C++ encoder/decoder experiment combining adaptive Huffman coding with run-length encoding |
| [Lake message dispatch](projects/lake/) | 2002 C++ experiment in object messaging |
| [Matrix math](projects/matrixMath/) | 2002 C++ 3D math experiment with `Matrix4`, vector operations, overloaded arithmetic and a test driver |
| [Onyx Direct3D screen experiment](projects/onyx/) | Direct3D 8 screen-management and vertex-buffer experiment |

## Code worth opening

- [Adaptive Huffman and run-length coding](projects/huffman/main.cpp) documents the interaction of two compression techniques in an early C++ implementation.
- [Recursive terrain generation](projects/fract01/makeTerrain.cpp#L112) passes a roughness parameter through a recursive height-field subdivision.

[Study archive](coursework/) records the provenance of mixed-origin university material. Project notes identify
author credits where the files support them. The source snapshots retain historical build files and original credits.
