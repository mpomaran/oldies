/*
**      Konwerter pliku ASC na A0
**
**      Michal Pomaranski
*/

#include <stdio.h>
#include <string.h>

char *keywords[8] = { "Vertices:", "X:", "Y:", "Faces:",
                    "Z:", };

int main (int argc, char *argv[])
{
  FILE *in, *out, *temp;
  char ciag[255];
  int i;
  float number;
  int objectsNo=0;
  int goodFlag = 0;

  printf ("ASC to A0 file converter. Michal Pomaranski.\n");
  printf ("This is a part of ONYX 3d Lib. Copyright (c) 2000 by MP\n\n");

  if (argc != 3)
  {
    printf ("usage: asc2a0 [in] [out]\n");
    return -1;
  }

  in = fopen (argv[1], "rt");
  temp = fopen ("temp2.tmp", "wt");

  /* wyrzucamy wszystkie objekty, ktore nie sa interesujace */
  while (!feof(in))
  {
    int c, count;
    char ciag2[255];

    fscanf (in, "%s", ciag);
    /* poszukujemy poczatku objektu */
    if (!strcmp (ciag, "Face"))
    {
      fscanf (in, "%s", ciag2);
      if (!strcmp(ciag2, "list:"))
         strcpy (ciag, "");
      else
      {
         fprintf (temp, "%s ", ciag);
         strcpy (ciag, ciag2);
      }
    }

    if (!strcmp (ciag, "Named"))
    {
      count=0;
      do
      {
         c=fgetc(in);
         if (c == '"') count++;
      }
      while (count != 2);
      fscanf (in, "%s", ciag2);
      if (strcmp(ciag2, "Tri-mesh,"))
      {
         goodFlag=0;
         printf ("Unknown object has been found.\n");
      }
      else
      {
         printf ("Object has been found.\n");
         goodFlag=1;
         fprintf (temp, " object ");
      }
    }
    if (goodFlag) fprintf (temp, "%s ", ciag);
  }

  fclose(in); fclose (temp);
  in = fopen ("temp2.tmp", "rt");
  temp = fopen ("temp.tmp", "wt");

  /* preprocessing */
  while (!feof(in))
  {
    int c;

    c = fgetc(in);
    if (c == ':')
    {
      fputc(':', temp);
      fputc(' ', temp);
    } else fputc (c, temp);
  }
  fclose(temp);
  fclose(in);

  in = fopen ("temp.tmp", "rt");
  out = fopen (argv[2], "wt");
  if (!in || !out)
  {
    printf ("I/O Error\n");
    return -1;
  }

  /* ile objektow jest w pliku? */
  while (!feof (in))
  {
    fscanf(in, "%s", ciag);
    if (!strcmp (ciag, "object"))
       objectsNo++;
  }
  printf ("\n----------------------------------\n%d object(s) has been found.\n", objectsNo);
  fseek (in, 0, SEEK_SET);

  fprintf (out, "%d ", objectsNo);
  while (!feof (in))
  {
    int ab, bc, ca, a, b, c;
    fscanf (in, "%s", ciag);

    /* czy wazna liczba? */
    for (i=0; i<5; i++)
        if (!stricmp (ciag, keywords[i]))
        {
          fscanf (in, "%f", &number);
          if (number == (int)number)
          {
                fprintf (out, "%d ", (int)number);
          }
          else
                fprintf (out, "%f ", number);
        }

    /* Teraz ukladaymy face w porzadku */
    if (!stricmp (ciag, "Face"))
    {
     char ch;
     int bit;

      while ( (ch=fgetc(in)) != ':' ); /* pomijamy nr face'a */

      fscanf (in, "%s", ciag);  /* pomijamy smiecie */
      fscanf (in, "%d", &a);    /* to jest vertex a  */
      fscanf (in, "%s", ciag);
      fscanf (in, "%d", &b);    /* to jest vertex b  */
      fscanf (in, "%s", ciag);
      fscanf (in, "%d", &c);    /* to jest vertex c  */

      fscanf (in, "%s", ciag);
      fscanf (in, "%d", &ab);   /* kolejnosc vertexow */
      fscanf (in, "%s", ciag);
      fscanf (in, "%d", &bc);
      fscanf (in, "%s", ciag);
      fscanf (in, "%d", &ca);

      bit = ab + bc*2 + ca*4;

      switch (bit)
      {
        case 0:
         fprintf (out, "%d %d %d ", c, b, a);
         break;
        case 1:
         fprintf (out, "%d %d %d ", c, b, a);
         break;
        case 2:
         fprintf (out, "%d %d %d ", a, b, c);
         break;
        case 3:
         fprintf (out, "%d %d %d ", a, b, c);
         break;
        case 4:
         fprintf (out, "%d %d %d ", a, b, c);
         break;
        case 5:
         fprintf (out, "%d %d %d ", a, b, c);
         break;
        case 6:
         fprintf (out, "%d %d %d ", a, b, c);
         break;
        case 7:
         fprintf (out, "%d %d %d ", a, b, c);
         break;
      }
    }
  }

  fclose (in);
  fclose (out);

  remove ("temp.tmp");
  remove ("temp2.tmp");


  printf ("File converted. Exiting.");

  return 0;
}