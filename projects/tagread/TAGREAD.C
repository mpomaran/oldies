/*
**      Program odczytuje tagi z plikow MP3 i umieszcza
**      je w pliku podanym jako pierwszy parametr
**
**      PUBLIC DOMAIN
**
**          sorry za lamerski styl i brak komentarzy, ale spieszylo mi sie.
**                sarin@grzes.czart.pulawy.pl
*/

#include <stdio.h>

#define TAG_ID  "TAG"
#define TAG_LEN (128)

/* funkcja pomocnicza */
int info(char *txt, int len)
{
 int i;

   for (i=0; i<len; i++)
     if (txt[i] != ' ' && txt[i] != 0x0d && txt[i] != 0x00)
        return 1;

   return 0;
}

/* MAIN */
int main(int argc, char *argv[])
{
  int i,j;
  FILE *mp3;
  FILE *out;
  char *buff;
  char *tag;
  int  filelen;

        if (argc < 3)
          {
            printf("TagRead 0.1 by MechWarrior. PUBLIC DOMAIN\n");
            printf("usage: tagread <output> <mp3 files>\nWildcards not allowed.\n");
            return 0;
          }

        out = fopen(argv[1],"at");
        if (out == NULL)
          {
            printf("tagread: can't open \"%s\" file",argv[1]);
            return 0;
          }

        buff = (char *)malloc (TAG_LEN);
        if (buff == NULL)
          {
             printf("tagread: error - not enough memory\n");
             return 0;
          }

        for (i=0; i<argc-2; i++)
          {
            mp3 = fopen(argv[i+2], "rb");
            if (mp3 == NULL)
              {
                fprintf(out, "\"%s\" file not found...\n", argv[i+2]);
                printf("tagread: \"%s\" file not found\n", argv[i+2]);
                continue;
              }

            if (fseek(mp3, 0, SEEK_SET))
                perror("tagread");

            if (fseek(mp3, -TAG_LEN, SEEK_END))
                perror("tagread");

            fread(buff, TAG_LEN, 1, mp3);
            if (ferror(mp3))
               perror("tagread");

            fprintf(out, "file: %s\n",argv[i+2]);
            if (buff[i] == TAG_ID[0] && buff[i+1] == TAG_ID[1]
                && buff[i+2] == TAG_ID[2])
              {
                tag = buff+3;
                if (info(tag,30))
                       fprintf(out,"\ttitle:    %.30s\n",tag);

                if (info(tag+30,30))
                       fprintf(out,"\tartist:   %.30s\n",tag+30);

                if (info(tag+60,30))
                       fprintf(out,"\talbum:    %.30s\n",tag+60);

                if (info(tag+90,4))
                       fprintf(out,"\tyear:     %.4s\n",tag+90);

                if (info(tag+94,30))
                       fprintf(out,"\tcomment:  %.30s\n",tag+94);
              }
            else
            ;
//                 fprintf(out,"\tno mpeg file info available\n");

            fseek(mp3,0,SEEK_END);
            filelen = ftell(mp3);

            fprintf(out,"\tfile len: %.4f (Mb)\n",(float)filelen/(1024.*1024.));
            fprintf(out,"\n");

            fclose(mp3);
          }
        free(buff);
        fclose(out);
        return 1;
}
