#include "flash.h"

void    flash(int *buff, char color)
{
 int *end;
 int c;

 c = ((int)color)|((int)color<<8)|((int)color<<16)|((int)color<<24);
 end = buff + 320*200/4;

 while(buff<end) *buff++ = c;
}

