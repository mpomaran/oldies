/*
**      GIF2ONT converter
**
**      PUBLIC DOMAIN
**
**              this is a part of Onyx 3d LIB
*/

#include <stdio.h>
#include <eos.h>

int main (int argc, char *argv[])
{
 char *gif;
 FILE *out;
 float dx, dy;
 float x, y;

        printf ("    þ GIF to ONT converter\n");
        printf ("    þ usage : gif2ont [in] [out]\n");

        // open files
        gif = load_external_gif_handle(argv[1]);
        if (!gif)
        {
                printf ("    þ file load error\n");
                return -1;
        }
        out = fopen (argv[2], "wb");
        if (!out)
        {
                printf ("    þ file write error\n");
                return -1;
        }

        // save converted file

        // save palette
        printf ("    þ saving palette...");
        fwrite(gif_palette, 256, 3, out);
        printf ("OK\n");

        // compute deltas
        printf ("    þ computing deltas: ");
        dx = (float)gif_x/256.;
        dy = (float)gif_y/256.;
        printf ("gifX=%d, gifY=%d, dx=%f, dy=%f\n", gif_x, gif_y, dx, dy);
        printf ("    þ writing ONT file...");
        for (y=0; y<gif_y; y+=dy)
            for (x=0; x<gif_x; x+=dx)
                fputc(*(gif+(int)x+((int)y*gif_x)), out);
        fclose(out);
        printf ("OK\n");
        return 0;
}

