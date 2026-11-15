/* Funkcja przeprowadza tzw. motion blur :)             */

/* WE: bufor z ktorego pobieramy dane            */
/*     bufor do ktorego bedzie zapisywany motion */
void    blur(char *inBuff, char *outBuff)
{
  int addr;             /* offset obrazu */
  int color;

  for (addr=320;addr<(320-1)*200-120; addr++){
      color = inBuff[addr - 320] + inBuff[addr + 320] + inBuff[addr + 1] + inBuff[addr - 1];
      color >>= 2;

      outBuff[addr] = color;
  }
}



