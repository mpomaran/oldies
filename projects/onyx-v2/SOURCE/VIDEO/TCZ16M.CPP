/*
**      Texture mapper. MechWarrior. Z-Buffer implemented.
**
**      beta version
**
**
** clipping by Mats Byggmastar, mri@penti.sit.fi, 17.4.1997 Jakobstad, Finland
**      written in pure C... I've to change it!!! Soon!!!
**
**              (c) 2000 by MechWarrior
**                  don't rip this code 'coz it's pretty slow
**                  write something faster instead
*/

#include "mappers.h"
#include "..\misc\defs.h"

inline int cliptestx(vertex2d * v)
{
    int bits = 0;
    if(v->y < LeftClip)     bits |= LEFT;
    if(v->y > RightClip)    bits |= RIGHT;
    return bits;
}

inline int cliptesty(vertex2d * v)
{
    int bits = 0;
    if(v->y < TopClip)      bits |= TOP;
    if(v->y > BotClip)      bits |= BOT;
    return bits;
}

/*
 *      vbp is a pointer to a vertex array. The first 3 vertices in that
 *      array is our source vertices. The rest of the array will be used
 *      to hold new vertices created during clipping.
 *
 *      you can then access the new vertices using the *final variable
 *
 *      function returns the number of vertices in the resulting polygon
 */

inline int ClipUV(vertex2d *** final, vertex2d * vbp)
{
    int max, n, dsti;
    static vertex2d * vp1[12], * vp2[12];     // vertex ptr buffers
    vertex2d ** src = vp1;
    vertex2d ** dst = vp2;
    vertex2d ** tmp;

    vp1[0] = vbp + 0;
    vp1[1] = vbp + 1;
    vp1[2] = vbp + 2;
    vp1[3] = vbp + 0;

    vbp += 3;       // Next free vertex

    dsti = 0;
    max = 3;

    // left clip

    for(n=0; n<max; n++) {
        vertex2d * src1 = src[n];             // current vertex
        vertex2d * src2 = src[n+1];           // next vertex
        if((src1->visible & LEFT) == VISIBLE) {
            dst[dsti++] = src1;                 // add visible vertex to list
            if((src2->visible & LEFT) == VISIBLE)
                continue;
        } else
            if((src2->visible & LEFT) != VISIBLE)
                continue;
        float a = (LeftClip - src1->x) / (src2->x - src1->x);
        float ima = 1.0-a;
        dst[dsti] = vbp++;                      // create new vertex
        dst[dsti]->y = src1->y*ima + src2->y*a;
        dst[dsti]->x = LeftClip;
        dst[dsti]->u = src1->u*ima + src2->u*a;
        dst[dsti]->v = src1->v*ima + src2->v*a;
        dst[dsti]->z = src1->z*ima + src2->z*a;
        dst[dsti]->visible = cliptesty(dst[dsti]);
        dsti++;
    }
    dst[dsti] = dst[0];
    tmp = src; src = dst; dst = tmp;            // Swap src - dst buffers
    max = dsti;
    dsti = 0;

    // right clip

    for(n=0; n<max; n++) {
        vertex2d * src1 = src[n];             // current vertex
        vertex2d * src2 = src[n+1];           // next vertex
        if((src1->visible & RIGHT) == VISIBLE) {
            dst[dsti++] = src1;                 // add visible vertex to list
            if((src2->visible & RIGHT) == VISIBLE)
                continue;
        } else
            if((src2->visible & RIGHT) != VISIBLE)
                continue;
        float a = (RightClip - src1->x) / (src2->x - src1->x);
        float ima = 1.0-a;
        dst[dsti] = vbp++;                      // create new vertex
        dst[dsti]->y = src1->y*ima + src2->y*a;
        dst[dsti]->x = RightClip;
        dst[dsti]->u = src1->u*ima + src2->u*a;
        dst[dsti]->z = src1->z*ima + src2->z*a;
        dst[dsti]->v = src1->v*ima + src2->v*a;
        dst[dsti]->visible = cliptesty(dst[dsti]);
        dsti++;
    }
    dst[dsti] = dst[0];
    tmp = src; src = dst; dst = tmp;            // swap src - dst buffers
    max = dsti;
    dsti = 0;

    // top clip
    for(n=0; n<max; n++) {
        vertex2d * src1 = src[n];             // current vertex
        vertex2d * src2 = src[n+1];           // next vertex
        if((src1->visible & TOP) == VISIBLE) {
            dst[dsti++] = src1;                 // add visible vertex to list
            if((src2->visible & TOP) == VISIBLE)
                continue;
        } else
            if((src2->visible & TOP) != VISIBLE)
                continue;
        float a = (TopClip - src1->y) / (src2->y - src1->y);
        float ima = 1.0-a;
        dst[dsti] = vbp++;                      // create new vertex
        dst[dsti]->x = src1->x*ima + src2->x*a;
        dst[dsti]->y = TopClip;
        dst[dsti]->u = src1->u*ima + src2->u*a;
        dst[dsti]->v = src1->v*ima + src2->v*a;
        dst[dsti]->z = src1->z*ima + src2->z*a;
        dst[dsti]->visible = cliptestx(dst[dsti]);
        dsti++;
    }
    dst[dsti] = dst[0];
    tmp = src; src = dst; dst = tmp;            // swap src - dst buffers
    max = dsti;
    dsti = 0;

    // bot clip

    for(n=0; n<max; n++) {
        vertex2d * src1 = src[n];             // current vertex
        vertex2d * src2 = src[n+1];           // next vertex
        if((src1->visible & BOT) == VISIBLE) {
            dst[dsti++] = src1;                 // add visible vertex to list
            if((src2->visible & BOT) == VISIBLE)
                continue;
        } else
            if((src2->visible & BOT) != VISIBLE)
                continue;
        float a = (BotClip - src1->y) / (src2->y - src1->y);
        float ima = 1.0-a;
        dst[dsti] = vbp++;                      // create new vertex
        dst[dsti]->x = src1->x*ima + src2->x*a;
        dst[dsti]->y = BotClip;
        dst[dsti]->u = src1->u*ima + src2->u*a;
        dst[dsti]->v = src1->v*ima + src2->v*a;
        dst[dsti]->z = src1->z*ima + src2->z*a;
        dsti++;
    }

    *final = dst;

    return dsti;
}

struct sekcja{
        int dx;
        int dz;         /* z-bufor              */
        int du;         /* wsp. u tekstury      */
        int dv;         /* wsp. z tekstury      */
};

/* uzywane przez mapper, po co 1000 razy deklarowac ? */
static int granica[2];
static struct sekcja l_sekcja[2], r_sekcja[2];

static int ddz;         /* stale delty (stale dla calego trojkata */
static int ddu;
static int ddv;

/* temp21y = v2->y - v1->y */
/* temp31y = v3->y - v1->y */
static float temp, temp21y, temp31y;
static int middle_left; /* czy srodkowy vertex lezy po lewo, czy po prawo */

static int l_x, r_x;    /* uzywane w petlach wewnetrznych                 */
static int l_z;
static int l_u, l_v;

static int y;
static int sekcja;
static int i;

static int z;         /* te 3 zmienne interpolujemy w petli wewn.    */
static int u,v;

static char *buffer;
static int  *zbuffer;
static unsigned char *text_r, *text_g, *text_b; /* skladowe koloru tekstury */

static int y_opt;       /* zoptymalizowana (pomnozona przez 320) */
                        /* wspolrzedna punktu na ekranie         */
//float k;

/* rysuje trojkat cieniowany gorouardem + z-bufor */
inline void  draw_triangle(struct vertex2d *v1,struct vertex2d *v2,
                                struct vertex2d *v3, char *buff, char *text,
                                int *zbuff)
{
        /* Sortowanie vertexow */

        if(v1->y > v2->y) { struct vertex2d * v = v1; v1 = v2; v2 = v; }
        if(v1->y > v3->y) { struct vertex2d * v = v1; v1 = v3; v3 = v; }
        if(v2->y > v3->y) { struct vertex2d * v = v2; v2 = v3; v3 = v; }

        /* jesli trojkat ma wysokosc 0, to po co go rysowac ? */
        /* przed opt. bylo :                                  */
        /*   if (v3->y == v1->y) return;                      */
        temp31y = v3->y - v1->y;
        if (!temp31y) return;

        temp21y = v2->y - v1->y;

        /* to rownanie wyprowadzilem sam, ale okazalo sie potem, */
        /* ze zostalo ono zamieszczone juz wczesniej na liscie   */
        /* comp.graphic.algorithm przez Pursey'a                 */
        temp = (v3->x-v1->x)*temp21y-(v2->x-v1->x)*temp31y;
        if (temp==0) return;
        if (temp > 0)
           middle_left = 1;
        else middle_left = 0;

        /* Rozbicie tekstury na 3 skladowe koloru                */
        text_r = text;
        text_g = text + 0x10000;
        text_b = text + 0x20000;

        /* Obliczenie delt i roznych takich    */
        /* Zakladam, ze vertexy sa posortowane */
        granica[0] = v2->y;
        granica[1] = v3->y;

        if (middle_left)
          {             /* vertex 2 po lewej stronie */
                if (temp21y)
                  {
                    /* mnoze, zamiast przesuwac - kompilator to i tak */
                    /* zoptymalizuje, a ja nie musze martwic sie      */
                    /* o zachowanie znaku                             */
                    l_sekcja[0].dx = ((v2->x - v1->x) * 0x10000) / temp21y;
                    l_sekcja[0].dz = ((v2->z - v1->z) * 0x10000) / temp21y;
                    l_sekcja[0].du = ((v2->u - v1->u) * 0x10000) / temp21y;
                    l_sekcja[0].dv = ((v2->v - v1->v) * 0x10000) / temp21y;
                  }

                temp = v3->y - v2->y;
                if (temp)
                  {
                    l_sekcja[1].dx = ((v3->x - v2->x) * 0x10000) / temp;
                    l_sekcja[1].dz = ((v3->z - v2->z) * 0x10000) / temp;
                    l_sekcja[1].du = ((v3->u - v2->u) * 0x10000) / temp;
                    l_sekcja[1].dv = ((v3->v - v2->v) * 0x10000) / temp;
                  }

                r_sekcja[0].dx = r_sekcja[1].dx
                               = ((v3->x - v1->x) * 0x10000) / (v3->y - v1->y);
          }
        else
          {             /* vertex 2 po prawej stronie */
                if (temp21y)
                    r_sekcja[0].dx = ((v2->x - v1->x) * 0x10000) / temp21y;

                temp = v3->y - v2->y;
                if (temp)
                    r_sekcja[1].dx = ((v3->x - v2->x) * 0x10000) / temp;


                l_sekcja[0].dx = l_sekcja[1].dx
                                = ((v3->x - v1->x) * 0x10000) / temp31y;

                l_sekcja[0].dz = l_sekcja[1].dz
                                = ((v3->z - v1->z) * 0x10000) / temp31y;

                l_sekcja[0].du = l_sekcja[1].du
                                = ((v3->u - v1->u) * 0x10000) / temp31y;

                l_sekcja[0].dv = l_sekcja[1].dv
                                = ((v3->v - v1->v) * 0x10000) / temp31y;
          }

        /* Rysowanie */
        sekcja = 0;
        y = v1->y;
        if (!temp21y)
          if (middle_left)
          {
            l_x = v2->x * 0x10000;
            r_x = v1->x * 0x10000;
            l_z = (int)v2->z * 0x10000;
            l_u = v2->u * 0x10000;
            l_v = v2->v * 0x10000;
          } else {
            l_x = v1->x * 0x10000;
            r_x = v2->x * 0x10000;
            l_z = (int)v1->z * 0x10000;
            l_u = v1->u * 0x10000;
            l_v = v1->v * 0x10000;
          }
        else
        {
            l_x = r_x = v1->x * 0x10000;
            l_z = (int)v1->z * 0x10000;
            l_u = v1->u * 0x10000;
            l_v = v1->v * 0x10000;
        }

        y_opt = y * scanlineLen;
        do      /* dopoki nie narysowano wszystkich sekcji */
          {
                while (y != granica[sekcja])
                {
                        buffer = buff + ((int)(l_x / 0x10000) + y_opt)*3;
                        zbuffer = zbuff + (int)(l_x / 0x10000) + y_opt;
                        z = l_z;
                        u = l_u / 0x100;
                        v = l_v / 0x100;

                        /* P E T L A    W E W N E T R Z N A           */
                        for (i = r_x - l_x; i > 0; i -= 0x10000)
                          {
                            if (z<*zbuffer && z>BehindClip)
                            {
                              buffer[0] =
                                   text_b[(v & 0xff00) + (u & 0xff00)/0x100];
                              buffer[1] =
                                   text_g[(v & 0xff00) + (u & 0xff00)/0x100];
                              buffer[2] =
                                   text_r[(v & 0xff00) + (u & 0xff00)/0x100];
                              *zbuffer = z;
                            }
                            buffer+=3;
                            zbuffer++;
                            z += ddz; v += ddv; u += ddu;
                          }

                        l_x += l_sekcja[sekcja].dx;
                        r_x += r_sekcja[sekcja].dx;
                        l_z += l_sekcja[sekcja].dz;
                        l_u += l_sekcja[sekcja].du;
                        l_v += l_sekcja[sekcja].dv;
                        y++;
                        y_opt += scanlineLen;
                }
                sekcja++;
          }
        while (sekcja < 2);
}

inline int cliptest(vertex2d * v)
{
    int bits = 0;
    if(v->y < TopClip)   bits |= TOP;
    if(v->y > BotClip)   bits |= BOT;
    if(v->x < LeftClip)  bits |= LEFT;
    if(v->x > RightClip) bits |= RIGHT;
    return bits;
}

void tClipZ16mTriangle (vertex2d *a, vertex2d *b, vertex2d *c, char *buff,
                         char *text, int *zbuff)
{
    a->visible = cliptest(a);
    b->visible = cliptest(b);
    c->visible = cliptest(c);

    int orbits  = a->visible | b->visible | c->visible;
    int andbits = a->visible & b->visible & c->visible;

    if(andbits != 0) return;

    if(a->y > b->y) { struct vertex2d * v = a; a = b; b = v; }
    if(a->y > c->y) { struct vertex2d * v = a; a = c; c = v; }
    if(b->y > c->y) { struct vertex2d * v = b; b = c; c = v; }

    /* Obliczanie delt - jak nie wiesz o co chodzi, to       */
    /* poczytaj sobie o tym w Fast Affine Texture Mapping    */
    /*  w skrocie sa to delty, ktore nie zmieniaja sie       */
    /*  podczas teksturowania trojkata                       */

    /* jesli trojkat ma wysokosc 0, to po co go rysowac ?    */
    temp31y = c->y - a->y;
    if (!temp31y) return;

    temp21y = b->y - a->y;

    /* to rownanie wyprowadzilem sam, ale okazalo sie potem, */
    /* ze zostalo ono zamieszczone juz wczesniej na liscie   */
    /* comp.graphic.algorithm przez Pursey'a                 */
    temp = (c->x-a->x)*temp21y-(b->x-a->x)*temp31y;


    ddz = ( (c->z - a->z) * temp21y
          - (b->z - a->z) * temp31y ) * 65536. / temp;
    ddu = ( (c->u - a->u) * temp21y
          - (b->u - a->u) * temp31y ) * 256. / temp;
    ddv = ( (c->v - a->v) * temp21y
          - (b->v - a->v) * temp31y ) * 256. / temp;

    // tutaj decydujemy, czy obcinac
    if((orbits & (TOP | BOT | LEFT | RIGHT)) == VISIBLE) {
        draw_triangle(a, b, c, buff, text, zbuff);
    }
    else {
        static vertex2d vc[12], ** dst;
        vc[0].x = a->x;
        vc[0].y = a->y;
        vc[0].u = a->u;
        vc[0].v = a->v;
        vc[0].z = a->z;
        vc[0].visible = a->visible;
        vc[1].x = b->x;
        vc[1].y = b->y;
        vc[1].u = b->u;
        vc[1].v = b->v;
        vc[1].z = b->z;
        vc[1].visible = b->visible;
        vc[2].x = c->x;
        vc[2].y = c->y;
        vc[2].u = c->u;
        vc[2].v = c->v;
        vc[2].z = c->z;
        vc[2].visible = c->visible;
        int max = ClipUV(&dst, vc);
        if(max < 3) return;

        for (int j=1; j<max-1; j++)
            draw_triangle(dst[0], dst[j], dst[j+1], buff, text, zbuff);
    }
}