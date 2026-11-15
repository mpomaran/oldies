/* Niniejszy program oparty jest na przykladzie 2.4.10 z ksiazki:
 * S.A. Rago, "UNIX System V Netowork Programming".
 * Pokazano, ze uzycie funkcji signal() do obslugi sygnalow jest
 * ryzykowne. Funkcja obslugi przerwania (handler) ma celowo wprowadzone
 * opoznienie pomiedzy momentem jej wywolania a ponowieniem deklaracji
 * obslugi sygnalu SIGINT (np. ^C z klawiatury), za pomoca
 *		signal(SIGINT,handler);
 * Jezeli sygnal przyjdzie przed wykonaniem powyzszej linii, to obsluga
 * sygnalu bedzie standardowa, tzn. zakonczenie dzialania programu
 * (patrz signal(5)). Dla systemu Solaris 2.5:
     Name       Value  Default  Event

     SIGHUP       1    Exit     Hangup (see termio(7I))
     SIGINT       2    Exit     Interrupt (see termio(7I))
     SIGQUIT      3    Core     Quit (see termio(7I))
     SIGILL       4    Core     Illegal Instruction
     SIGTRAP      5    Core     Trace/Breakpoint Trap
     SIGABRT      6    Core     Abort
     SIGEMT       7    Core     Emulation Trap
     SIGFPE       8    Core     Arithmetic Exception
     SIGKILL      9    Exit     Killed
     SIGBUS       10   Core     Bus Error
     SIGSEGV      11   Core     Segmentation Fault
     SIGSYS       12   Core     Bad System Call
     SIGPIPE      13   Exit     Broken Pipe

     SIGPIPE      13   Exit     Broken Pipe
     SIGALRM      14   Exit     Alarm Clock
     SIGTERM      15   Exit     Terminated
     SIGUSR1      16   Exit     User Signal 1
     SIGUSR2      17   Exit     User Signal 2
     SIGCHLD      18   Ignore   Child Status Changed
     SIGPWR       19   Ignore   Power Fail/Restart
     SIGWINCH     20   Ignore   Window Size Change
     SIGURG       21   Ignore   Urgent Socket Condition
     SIGPOLL      22   Exit     Pollable Event (see streamio(7I))
     SIGSTOP      23   Stop     Stopped (signal)
     SIGTSTP      24   Stop     Stopped (user) (see termio(7I))
     SIGCONT      25   Ignore   Continued
     SIGTTIN      26   Stop     Stopped (tty input) (see termio(7I))
     SIGTTOU      27   Stop     Stopped (tty output) (see termio(7I))

     SIGTTOU      27   Stop     Stopped (tty output) (see termio(7I))
     SIGVTALRM    28   Exit     Virtual Timer Expired
     SIGPROF      29   Exit     Profiling Timer Expired
     SIGXCPU      30   Core     CPU time limit exceeded (see
                                getrlimit(2))
     SIGXFSZ      31   Core     File size limit exceeded (see
                                getrlimit(2))
     SIGWAITING   32   Ignore   Concurrency signal reserved by threads library
     SIGLWP       33   Ignore   Inter-LWP signal reserved by threads library
     SIGFREEZE    34   Ignore   Check point Freeze
     SIGTHAW      35   Ignore   Check point Thaw
     SIGCANCEL    36   Ignore   Cancellation signal reserved by threads library
     SIGRTMIN     *    Exit     First real time signal
     (SIGRTMIN+1) *    Exit     Second real time signal
      ...
     (SIGRTMAX-1) *    Exit     Second-to-last real time signal
     SIGRTMAX     *    Exit     Last real time signal
          (The symbols SIGRTMIN through SIGRTMAX are evaluated
          dynamically in order to permit future configurability)
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
	signal(SIGINT,handler);
	i=getpid();
	printf("Wywolany program %s ma pid=%d\n",argv[0],i);
/*
 *	Pauzuj 10 razy. pause() blokuje az do otrzymania sygnalu.
 */
	for(i=0; i<10; i++){
		printf("Czekam na sygnal\n");
		pause();
		printf("Otrzymalem sygnal\n");
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
/*
 *	Reinstaluj funkcje obslugi sygnalu
 */
	signal(SIGINT,handler);
}
