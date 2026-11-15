# MINIX process messaging labs

Two C programs from April 2002, recovered from the study backup's `Laborki.zip`.

- [`testuj.c`](testuj.c) exercises a lab system call for looking up the process-table slot.
- [`product.c`](product.c) sets up a producer, a consumer and an intermediary buffer and uses MINIX message passing. The source credits Michal Pomaranski and prefixes its diagnostic messages with `kiwi:`.

The surrounding coursework includes modifications to the MINIX memory manager and kernel message handling, with
`kiwi` tags by some changes. The MINIX system sources are preserved in the original local backup. The published
test programs target the lab's modified MINIX environment and have not been run here.
