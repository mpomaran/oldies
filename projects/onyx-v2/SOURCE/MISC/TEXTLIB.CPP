//
//      Procedury zarzadzajace teksturami (zapis, odczyt, znajdowanie, itp
//
//

unsigned char colorTable[256][256];      /* tablica definiujaca cienie */

char* convertTexture(char *buffer)
{
  char *result;
  unsigned char *palette;
  unsigned char *texture;
  int  i;

        result = new char[256*256*3];
        if (!result)
           return 0;

        palette = buffer;
        texture = buffer+256*3;

        for (i=0; i<256*256; i++)
        {
         unsigned char c;

          c = texture[i];
          result[i] = palette[c*3]*4;
          result[i+256*256] = palette[c*3+1]*4;
          result[i+256*256*2] = palette[c*3+2]*4;
        }

        return result;
}
