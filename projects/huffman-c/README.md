# Huffman in C

A small Huffman compressor from November 2000. It counts symbols, builds a tree with a priority queue, and writes the codes through a bit I/O layer.

- [cmprss.c](cmprss.c) ties the encoding steps together.
- [tree.c](tree.c) and [queue.c](queue.c) build the tree.
- [bitio.c](bitio.c) reads and writes bits across byte boundaries.

The original [driver](main.c) reads 200,000 bytes from `test.in` and writes `test.out`. There's also a [later C++ experiment](../huffman/) with adaptive coding.
