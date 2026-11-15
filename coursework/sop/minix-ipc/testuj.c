/*
 *	Program testujacy modyfikacje jadra
 *
 *	Michal Pomaranski
 */

#include "/usr/include/lib.h"
#include <stdio.h>		/* printf 	*/
#include <unistd.h>		/* getpid 	*/
#include <errno.h>		/* errno	*/
#include <string.h>		/* strerror	*/

int main ( void )
{
	message	msg;
	int	result;

	msg.m1_i1 = getpid ();
/*	msg.m1_i1 = 62; */
	result = _syscall (MM, GETPROCNR, &msg);

	if (result == -1)	/* blad ? */
	{	
		printf ("_syscall zwrocil blad nr: %d: %s\n", errno, strerror (errno));
		result = _syscall (MM, GETPROCNR, &msg);

		getchar ();

		printf ("Numer procesu %d w tablicy procesow to %d.\n", 
			getpid(), result);

		return -1;
	}

	/* wszysko ok */
	printf ("Numer procesu %d w tablicy procesow to %d.\n", 
		getpid(), result);

	printf ("Nacisnij klawisz aby zakonczyc...\n");
	getchar ();

	return 0;	/* sukces */
}

