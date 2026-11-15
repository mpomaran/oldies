/* Niniejszy program oparty jest na przykladzie 2.4.11 z ksiazki:
 * S.A. Rago, "UNIX System V Netowork Programming".
 * Pokazano, ze uzycie funkcji sigset() zamiast funkcji signal()
 * do obslugi sygnalow likwiduje ryzyko zlej obslugi dwoch sygnalow
 * przychodzacych zbyt szybko.
 * Funkcja obslugi przerwania (handler) ma celowo wprowadzone
 * opoznienie, aby pokazac odpornosc obslugi sygnalu na pojawienie sie
 * nowego sygnalu w trakcie obslugi poprzedniego. Ten drugi sygnal czeka
 * na skonczenie przez funkcje handler() obslugi poprzedniego sygnalu.
 * (Pytanie: co stanie sie, jezeli w czasie jednej sekundy przyjda
 * wiecej niz 2 sygnaly?).
 * 
 * Ostatnia modyfikacja programu: 11/10/1996 - L.J. Opalski 
 */
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
void main(int argc, char *argv[])
{
	int i;
	void handler(int);
/*
 *	Instaluj funkcje obslugi sygnalu SIGINT
 */
	sigset(SIGINT,handler);
	i=getpid();
	printf("Wywolany program %s ma pid=%d\n",argv[0],i);
/*
 *	Pauzuj 10 razy. pause() blokuje az do otrzymania sygnalu.
 */
	for(i=0; i<10; i++){
		printf("Oczekiwanie (nr %d) na sygnal\n",i+1);
		pause();
		printf("Otrzymalem sygnal(y)\n");
	}
}
void handler(int sig)
{
	printf("obsluga sygnalu SIGINT\n");
	
/*
 *	Poczekaj chwile, dajac szanse na sprawdzenie co sie stanie
 *	jesli nowy sygnal przyjdzie przed ponownym zainstalowaniem
 *	funkcji obslugi sygnalu: handler()
 */
	sleep(1);
}
