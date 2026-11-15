/* Funkcja przeprowadza tzw. motion blur :)             */

// Wlasciwie to ten kawalek jest odpowiedzialny za blur
void blurInner(char *src, char *dst);
#pragma aux blurInner =   \
"       mov ecx, 64000-640"      \
"blurLoop:"                      \
"       movzx  eax, [esi - 320]" \
"       movzx  ebx, [esi + 320]" \
"       add  ax, bx"             \
"       mov  bl, [esi + 1]"      \
"       add  ax, bx"             \
"       mov  bl, [esi - 1]"      \
"       add  ax, bx"             \
"       shr  ax, 2"              \
"       mov [edi], al"           \
"       inc esi"                 \
"       inc edi"                 \
"       loop blurLoop"           \
        modify [eax ecx ebx]     \
        parm [esi] [edi];


void    blur(char *inBuff, char *outBuff)
{
  int i;

  blurInner(inBuff+320, outBuff+320);

  for (i=0; i<80; i++)        // czyszczenie paska na dole ekranu
      *((int *)outBuff + i + 16000-80) = 0;
}



