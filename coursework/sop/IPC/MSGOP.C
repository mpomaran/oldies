/* 
 * msgop.c: illustrates the msgsnd() and msgrcv() functions.
 * It allows the user to attempt to send ad receive as many messages
 * as wanted to or from one message queue.
 * Based on the code in "SunOS 5.2 System Services"
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <time.h>
static int ask();
static char first_on_queue[]="-> first message on queue",
	full_buf[]="Message buffer overflow. Extra message text discareded.";

void main()
{
	register int	c;	/* message text input */
	int		choice;	/* user's selected operation code */
	register int	i;	/* loop control for mtext */
	int     	msgflg;	/* message flags for the operation */
	struct msgbuf	*msgp;	/* pointer to the message buffer */
	int		msgsz;	/* message size */
	long		msgtyp;	/* desired message type */
	int  		msqid,	/* message queue ID to be used */
			maxmsgsz,	/* size of allocated message buffer */
			rtrn;	/* return value from msgrcv or msgsnd */

	(void) fprintf(stderr,
		"All numeric input is expected to follow C convenctions:\n");
	(void) fprintf(stderr,"\t0x... is interpreted as hexadecimal,\n");
	(void) fprintf(stderr,"\t0...  is interpreted as octal,\n");
	(void) fprintf(stderr,"\t0 otherwise, decimal\n");

/*
 * get the msqid and set up the message buffer.
 */
	(void) fprintf(stderr,"\nEnter the msqid: ");
	(void) scanf("%i",&msqid);
	(void) fprintf(stderr,"\nEnter the message buffer size you want: ");
	(void) scanf("%i",&maxmsgsz);
	if(maxmsgsz<0){
		(void) fprintf(stderr,
		"msgop: The message buffer size must be >= 0.\n");
		exit(1);
		/*NOTREACHED*/
	}
	msgp=(struct msgbuf *)malloc((unsigned)(sizeof(struct msgbuf)-
		sizeof(msgp->mtext)+maxmsgsz));
	if(msgp==NULL){
		(void) fprintf(stderr,
		"msgop: Could not alocate message buffer for %d byte messages",
		maxmsgsz);
		exit(1);
		/*NOTREACHED*/
	}
/*
 * Loop through message operations until the user is ready to quit.
 */
	while(choice=ask()){
	switch(choice){
	case 1:
		(void) fprintf(stderr,
"\nValid msgsnd message types are positive integers\nEnter msgp->mtype: ");
		(void) scanf("%li",&msgp->mtype);
		if(maxmsgsz){
/*
 * Throw away the rest of the input line after mtype, before reading the mtext.
 */
			while( (c=getchar()) != '\n' && c != EOF) ;
			(void) fprintf(stderr,"Enter a one line message:\n");
			for(i=0; ((c=getchar())!='\n'); i++){
				if(i>=maxmsgsz){
					(void)fprintf(stderr,"\n%s\n",full_buf);
					while((c=getchar())!='\n');
					break;
				}
				msgp->mtext[i]=c;
			}
			msgsz=i;
		} else
		msgsz=0;
		(void) fprintf(stderr,"\nMeaningful msgsnd flag is:\n");
		(void) fprintf(stderr,"\tIPC_NOWAIT =\t%#8.8o\n",IPC_NOWAIT);
		(void) fprintf(stderr,"Enter msgflg (0=default): ");
		(void) scanf("%i",&msgflg);
		(void) fprintf(stderr,
		"msgop: Calling msgsnd(%d,msgp,%d,%#o)\n",msqid,msgsz,msgflg);
		(void) fprintf(stderr,"msgp->mtype = %ld\n",msgp->mtype);
		(void) fprintf(stderr,"msgp->mtext = \"");
		for(i=0; i<msgsz; i++)
			(void) fputc(msgp->mtext[i],stderr);
		(void) fprintf(stderr,"\"\n");

		rtrn=msgsnd(msqid,msgp,msgsz,msgflg);
		if(rtrn==-1)
			perror("msgop: msgsnd failed");
		else
			(void) fprintf(stderr,
			"msgop: msgsnd returned %d\n",rtrn);
		break;
	case 2:
		for(msgsz=-1; msgsz<0 || msgsz>maxmsgsz;
				(void) scanf("%i",&msgsz))
			(void) fprintf(stderr,"%s (0 <= msgsz <= %d): ",
				"Enter msgsz",maxmsgsz);
		(void) fprintf(stderr,"msgtyp meanings:\n");
		(void) fprintf(stderr,"\t 0 %s\n",first_on_queue);
		(void) fprintf(stderr,"\t>0 %s of given type\n",
				first_on_queue);
		(void) fprintf(stderr,"\t<0 %s with type <= |msgtyp|\n",
			first_on_queue);
		(void) fprintf(stderr,"Enter msgtyp: ");
		(void) scanf("%li",&msgtyp);

		(void) fprintf(stderr,"meaningful msgrcv flags are:\n");
		(void) fprintf(stderr,"\tMSG_NOERROR=\t%#8.8o\n",
			MSG_NOERROR);
		(void) fprintf(stderr,"\tMSG_NOWAIT =\t%#8.8o\n",
			IPC_NOWAIT);
		(void) fprintf(stderr,"Enter msgflg: ");
		(void) scanf("%i",&msgflg);
		(void) fprintf(stderr,
	"\nmsgop: Calling msgrcv(%d,msgp,%d,%ld,%#o)\n",
			msqid,msgsz,msgtyp,msgflg);
		rtrn=msgrcv(msqid,msgp,msgsz,msgtyp,msgflg);
		if(rtrn==-1){
			perror("msgop: msgrcv failed");
			exit(1);
		/*NOTREACHED*/
		} else {
			(void) fprintf(stderr,
				"msgop: msgctl returned %d\n",rtrn);
			(void) fprintf(stderr,"msg->mtype = %ld\n",msgp->mtype);
			(void) fprintf(stderr,"msg->mtext is \"");
			for(i=0; i<rtrn; i++)
				(void) fputc(msgp->mtext[i],stderr);
			(void) fprintf(stderr,"\"\n");
		}
		break;
	default:
		(void) fprintf(stderr,"msgop: operation unknown\n");
		break;

	} /* switch */
	}/* while */
	exit(0);
	/*NOTREACHED*/
}
static
ask()
{
	int response; /* User's response */
	do {
		(void) fprintf(stderr,"Your options are:\n");
		(void) fprintf(stderr,"\tExit = \t0 or Control-D\n");
		(void) fprintf(stderr,"\tmsgsnd =\t1\n");
		(void) fprintf(stderr,"\tmsgrcv =\t2\n");
		(void) fprintf(stderr,"Enter your choice: ");
		response=0;
		(void) scanf("%i",&response);
	} while (response<0 || response >2);
	return(response);
}
