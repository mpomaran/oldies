/*======================================================================*
 *	Program testowy - producent-konsument				*
 *									*
 *	AUTOR: Michal Pomaranski					*
 *======================================================================*/

#include <stdlib.h>
#include <minix/com.h>		/* send etc. */
#include <lib.h>		/* _sendrec */
#include <stdio.h>		/* printf */
#include <signal.h>		/* kill? */

#include <unistd.h>

/*======================================================================*
 *	TYPY, FUNKCJE ITP.
 *======================================================================*/

#define		BUFF_LEN 5

#define 	_REQUEST m_type
#define		_PRODUCT_ID m1_i1
#define		_REPLY m1_i2
#define		_SRC m_source

#define		_PUT	1
#define		_GET	2

#define		_WAIT	1
#define		_OK	0
#define		_FULL	2
#define		_EMPTY	3

int	sys_call (int, int, message *);

void	bufferProc ( void );
void	clientProc ( void );
void	factoryProc ( void );
int	getProcNo ( pid_t );

int	_send (int, message *);
int	_receive (int, message *);
int 	_sendrec (int, message *);

#define send _send
#define receive _receive
#define sendrec _sendrec

#define SAFE_KILL(proc) if (proc>0) kill (proc, SIGKILL)

/*======================================================================*
 * GLOBALNE
 *======================================================================*/

pid_t	factoryPid;
pid_t	clientPid;
pid_t	buffPid;

/* numery w tablicy */
int	fact, client, buff;

/* wiadomosc musi byc globalna */
message msg;

#define TIME_ENTRY	10
int	factTime [TIME_ENTRY] = {1, 2, 1, 1, 3, 1, 0, 0, 0, 3};
int	clientTime [TIME_ENTRY] = {1, 1, 0, 0, 1, 3, 3, 3, 3, 3};

/* bufor wiadmomosci */
message msgBuff[BUFF_LEN];
int	buffIndex;

/*======================================================================*
 *	M A I N
 *======================================================================*/

int main ( void )
{
	/* inicjacja zmiennych */
	buffPid = factoryPid = clientPid = 0;

	/* utworzenie procesow */
	switch (buffPid = fork ())
	{
		case -1:
			printf ("kiwi: nie moge utorzyc bufora\n");
			goto end;
		case 0:
			buff = getProcNo (buffPid);
			bufferProc ();
			exit (0);
		default:
			buff = getProcNo (buffPid);
			printf ("kiwi: bufor utworzony: pid=%d, proc=%d\n",
				buffPid, buff);
	}

	switch (factoryPid = fork ())
	{
		case -1:
			printf ("kiwi: nie moge utworzyc procesu\n");
			goto end;
		case 0:
			fact = getProcNo (factoryPid);
			factoryProc ();
			exit (0);
		default:
			fact = getProcNo (factoryPid);
			printf ("kiwi: producent utworzony: pid=%d, proc=%d\n",
				factoryPid, fact);
	}

	switch (clientPid = fork ())
	{
		case -1:
			printf ("kiwi: nie moge utorzyc klienta\n");
			goto end;
		case 0:
			client = getProcNo (clientPid);
			clientProc ();
			exit (0);
		default:
			client = getProcNo (clientPid);
			printf ("kiwi: klient utworzony: pid=%d, proc=%d\n",
				clientPid, client);
	}

	

	/* czekamy na koniec */
	printf ("------------------------------------------------\n");
	printf ("Nacisnij ENTER...\n");
	printf ("------------------------------------------------\n\n");
	getchar();

			

	/* zabicie procesow */
end:
	SAFE_KILL (factoryPid);
	SAFE_KILL (clientPid);
	SAFE_KILL (buffPid);

	return 0;
}



/*======================================================================*
 * Obsluga FABRYKI
 *======================================================================*/
void factoryProc ( void )
{
	int	productCount=0;
	int	count=0;
	int	flag=0;

	while (1)
	{
		/* wyprodukowanie badziewia */
		msg._REQUEST=_PUT;
		msg._PRODUCT_ID=productCount++;
		msg._REPLY=_WAIT;
		msg._SRC=fact;

		printf ("producent: zrobilem i wyslalem %d.\n", msg._PRODUCT_ID);

		/* wyslanie badziewia w swiat */
		flag=0;	/* zeby nie zasypal nas komunikatami */
		while (msg._REPLY == _WAIT)
		{
			sendrec(buff, &msg);
			if (msg._REPLY == _FULL && !flag)
			{
				flag=1;
				printf ("producent: bufor pelny, czekam...\n");
			}
		}
		if (flag)
			printf ("producent: czekanie sie oplacilo\n");

		sleep(factTime[count]);

		/* zapewnia nieregularnosc produkcji */
		if (++count >= TIME_ENTRY)
			count = 0;
	}

	exit (0);
}



/*======================================================================*
 * Obsluga KLIENTA
 *======================================================================*/

void	clientProc ( void )
{
	int	count=0;
	int	flag;

	while (1)
	{
		msg._REQUEST=_GET;
		msg._REPLY=_WAIT;
		msg._SRC = client;
		
		/* pobieramy z kolejki produkt */
		
		flag=0;
		while (msg._REPLY != _OK)
		{
			sendrec (buff, &msg);
			if (msg._REPLY == _EMPTY && !flag)
			{
				flag=1;
				printf ("klient: bufor pusty, czekam...\n");
			}
		}
		if (flag)
			printf ("klient: czekanie sie oplacilo\n");

		/* konsumujemy */
		printf ("klient: dostalem i jem %d.\n", msg._PRODUCT_ID);

		/* nieregularnosc konsumpcji */
		sleep (clientTime[count]);
		if (++count >= TIME_ENTRY)
			count=0;

		printf ("klient: zjadlem %d\n", msg._PRODUCT_ID);
		
	}

	exit (0);
}



/*======================================================================*
 * obsluga BUFORA
 *======================================================================*/

void	bufferProc ( void )
{
	buffIndex=0;

	sleep (0);

	while (1)
	{
		receive(ANY, &msg);

		switch (msg._REQUEST)
		{
			case	_PUT:
				if (buffIndex >= BUFF_LEN)
				{	/* pelny bufor */
					msg._REPLY=_FULL;
				}
				else
				{
					/* buforujemy informacje */
					msgBuff[buffIndex++]._PRODUCT_ID=
						msg._PRODUCT_ID;
					msg._REPLY=_OK;
				}
		
				send (msg._SRC, &msg);
				break;
			case	_GET:
				if (buffIndex<=0)
				{	/* bufor pusty */
					msg._REPLY=_EMPTY;
				}
				else
				{
					msg._REPLY=_OK;
					msg._PRODUCT_ID = 
						msgBuff[--buffIndex]._PRODUCT_ID;
				}

				send (msg._SRC, &msg);
				break;
			default:
				printf (" OOPS!\n");
		}

		sleep(0);

	}

	exit (0);
}

/*======================================================================*
 * getProcNo 
 *======================================================================*/
int	getProcNo (pid_t pid)
{
	message msg;

	return _syscall (MM, GETPROCNR, &msg);
}

