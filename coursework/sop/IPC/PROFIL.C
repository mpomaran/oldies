#include <signal.h>
#include <unistd.h>

unsigned short bufor[4096];
main() {
int adres, koniec, skala, adrf,adrg,kod;
extern badaj(), f(), g();
signal(SIGINT,badaj);
koniec=(int)badaj;
adres= (int)main;
kod=(koniec-adres+sizeof(int)-1)/sizeof(int);
skala=0xffff;
printf("adres %d   koniec %d   kod %d\n", adres,koniec,kod);
adrf=(int) f;
adrg=(int) g;
printf("f %d   g %d   odl f %d   old g %d\n", adrf,adrg,adrf-adres,adrg-adres);
profil(bufor,sizeof(int)*kod,adres,skala);
for(;;) {
   f();
   g();
 }
}

f() {
}

g() {
}

badaj() {
int i;
for(i=0;i<4096;i++)
 if(bufor[i])
  printf("bufor[%d] = %d\n",i,bufor[i]);
 exit(0); 
}

