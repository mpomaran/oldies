/* 
 * msgget.c: illustrates the msgget() function. It prompts for the arguments,
 * makes the call, and reports the results.
 * Based on the code in "SunOS 5.2 System Services"
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
void main()
{
	key_t	key;	/* key to be passed to msgget() */
	int	msgflg,	/* msgflg to be passed to msgget() */
		msqid;	/* return value from msgget() */
	(void) fprintf(stderr,
		"All numeric input is expected to follow C convenctions:\n");
	(void) fprintf(stderr,"\t0x... is interpreted as hexadecimal,\n");
	(void) fprintf(stderr,"\t0...  is interpreted as octal,\n");
	(void) fprintf(stderr,"\t0 otherwise, decimal\n");
	(void) fprintf(stderr,"IPC_PRIVATE == %#lx\n",IPC_PRIVATE);
	(void) fprintf(stderr,"Enter key: ");
	(void) scanf("%li",&key);
	(void) fprintf(stderr,"\nExpected flags for msgflg argument are:\n");
	(void) fprintf(stderr,"\tIPC_EXCL=\t%#8.8o\n",IPC_EXCL);
	(void) fprintf(stderr,"\tIPC_CREAT=\t%#8.8o\n",IPC_CREAT);
	(void) fprintf(stderr,"\towner read=\t%#8.8o\n",0400);
	(void) fprintf(stderr,"\towner write=\t%#8.8o\n",0200);
	(void) fprintf(stderr,"\tgroup read=\t%#8.8o\n",040);
	(void) fprintf(stderr,"\tgroup write=\t%#8.8o\n",020);
	(void) fprintf(stderr,"\tother read=\t%#8.8o\n",04);
	(void) fprintf(stderr,"\tother write=\t%#8.8o\n",02);
	(void) scanf("%i",&msgflg);
	(void) fprintf(stderr,"\nmsgget: Calling msgget(%#lx,%#o)\n",
		key,msgflg);
	if( (msqid=msgget(key,msgflg)) == -1){
		perror("msgget: msgget failed");
		exit(1);
	} else {
		(void) fprintf(stderr,
		"msgget: msgget succeeded; msqid=%d\n",msqid);
		exit(0);
	}
	/*NOTREACHED*/
}
