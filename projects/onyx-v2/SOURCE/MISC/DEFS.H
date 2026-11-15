//
//      Definicje potrzebne dla mapperkow
//
//

#ifndef __DEFS_H
#define __DEFS_H

#define VISIBLE     0
#define TOP         1
#define BOT         2
#define LEFT        4
#define RIGHT       8

// granice obcinania
extern float LeftClip;
extern float RightClip;
extern float TopClip;
extern float BotClip;

extern int BehindClip;

/* dlugosc linii ekranu w bajtach */
extern unsigned scanlineLen;

#endif