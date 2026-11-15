# TagRead

A tiny C tool that reads ID3v1 tags from the last 128 bytes of MP3 files and appends the fields to a text file.

```text
tagread tags.txt track.mp3
```

[TAGREAD.C](TAGREAD.C) is the original MechWarrior version. It has an indexing bug in the tag check when you pass multiple files. Use one input file per invocation.
