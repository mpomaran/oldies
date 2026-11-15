/* 
 * shmop.c: illustrates the shmsnd() and shmrcv() functions.
 * It allows the user to attempt to send ad receive as many messages
 * as wanted to or from one message queue.
 * Based on the code in "SunOS 5.2 System Services"
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <time.h>
#define MAXnap	4	/* Maximum number of concurrent attaches */
static int ask();
static void catcher();
static int good_addr();

static struct state{	/* Internal record of currently attached segments */
	int	shmid;	/* shmid of attached segment */
	char	*shmaddr;	/* attach point */
	int	shmflg;	/* flags used on attach */
} ap[MAXnap];	/* State of currently attached segments */
static int	nap;	/* Number of currently attached segments */
static jmp_buf	segvbuf; /* Process state save area for SIGSEGV catching */

void main()
{
	register int	action;	/* action to be performed */
	char		*addr;	/* address work area */
	register int	i;	/* work area */
	register struct state *p;	/* ptr to current state entry */
	void	(*savefunc)();	/* SIGSEGV state hold area */
/*
 * Loop through message operations until the user is ready to quit.
 */
	while(action=ask()){
		if(nap){
			(void) fprintf(stderr,
				"\nCurrently attached segment(s):\n");
			(void) fprintf(stderr," shmid address\n");
			p=&ap[nap];
			while(p--!=ap){
				(void) fprintf(stderr,"%6d",p->shmid);
				(void) fprintf(stderr,"%#11x",p->shmaddr);
				(void) fprintf(stderr," Read%s\n",
					(p->shmflg&SHM_RDONLY)?
					"-Only":"/Write");
			}
		} else {
			(void) fprintf(stderr,
				"\nNo segments are currently attached.\n");
		}
	switch(action){
	case 1:	/* shmat requested */
/*
 * Verify that there is space for another attach
 */
		if(nap==MAXnap){
			(void) fprintf(stderr,
		"This example allows only %d attached segments\n",MAXnap);
			break;
		}
		p=&ap[nap++];
/*
 * Get the arguments, make the call, report the results, and update the current
 * state array.
 */
		(void) fprintf(stderr,"\nEnter shmid of segment to attach: ");
		(void) scanf("%i",&p->shmid);
		(void) fprintf(stderr,"\nEnter shmaddr: ");
		(void) scanf("%i",&p->shmaddr);
		(void) fprintf(stderr,"\nMeaningful shmflg values are:\n ");
		(void) fprintf(stderr,"\tSHM_RDONLY =\t%#8.8o\n",SHM_RDONLY);
		(void) fprintf(stderr,"\tSHM_RND    =\t%#8.8o\n",SHM_RND);
		(void) fprintf(stderr,"Enter shmflg value: ");
		(void) scanf("%i",&p->shmflg);
		(void) fprintf(stderr,"shmop: Calling shmat(%d,%#x,%#o)\n",
			p->shmid,p->shmaddr,p->shmflg);
		p->shmaddr=shmat(p->shmid,p->shmaddr,p->shmflg);
		if(p->shmaddr==(char *)-1){
			perror("shmop: shmat failed");
			nap--;
		} else {
			(void) fprintf(stderr,
			"shmop: shmat returned %#8.8x\n",p->shmaddr);
		}
		break;
	case 2:	/* shmdt requested */
/*
 * Get the address, make the call, report the results, and make
 * the internal state match
*/
		(void) fprintf(stderr,"Enter detach shmaddr: ");
		(void) scanf("%i",&addr);
		i=shmdt(addr);
		if(i==-1){
			perror("shmop: shmdt failed");
		} else {
			(void) fprintf(stderr,
		"shmop: shmdt returned %d\n",i);
			for(p=ap, i=nap; i--; p++){
				if(p->shmaddr==addr)
					*p=ap[--nap];
			}

		}
		break;
	case 3:	/* Read from segment requested */
		if(nap==0)
			break;
		(void) fprintf(stderr,"Enter addres of an attached segment:");
		(void) scanf("%i",&addr);
		if(good_addr(addr))
			(void) fprintf(stderr,"String @ %#x is '%s'\n",
				addr,addr);
		break;
	case 4:	/* Write to segment requested */
		if(nap==0)
			break;
		(void) fprintf(stderr,"Enter address of an attached segment: ");
		(void) scanf("%i",&addr);
/*
 * Set up SIGSEGV catch routine to trap attempts to write into
 * a read-only attached segment
 */
		savefunc=signal(SIGSEGV,catcher);
		if(setjmp(segvbuf)){
			(void) fprintf(stderr,
			"\nshmop: SIGSEGV signal caught. Write aborted\n");
		} else {
			if(good_addr(addr)){
				(void) fflush(stdin);
				(void) fprintf(stderr,
"Enter one line to be copied to shared segment attached @ %#x:\n",addr);
				(void) gets(addr);
/*				strcpy(addr,"tralala");*/
				printf("You entered:%s\n",addr);
			}
		}
		(void) fflush(stdin);
/*
 * Restore SIGSEGV to previous condition.
 */
		(void) signal(SIGSEGV,savefunc);
		break;
	} /* switch */
	}/* while */
	exit(0);
	/* NOTREACHED */
}
static
ask()
{
	int response; /* User's response */
	do {
		(void) fprintf(stderr,"Your options are:\n");
		(void) fprintf(stderr,"\t0 or Control-D=\texit\n");
		(void) fprintf(stderr,"\t1 = \tshmat\n");
		(void) fprintf(stderr,"\t2 = \tshmdt\n");
		(void) fprintf(stderr,"\t3 = read from segment\n");
		(void) fprintf(stderr,"\t4 = write to segment\n");
		(void) fprintf(stderr,"Enter your choice: ");
		response=0;
		(void) scanf("%i",&response);
	} while (response<0 || response >4);
	return(response);
}
/*ARGSUSED*/
/*
 * Catch signal caused by attempt to write into shared memory segment
 * attached with SHM_RDONLY flag set
 */
static void
catcher(sig)
{
	longjmp(segvbuf,1);
	/*NOTREACHED*/
}
/*
 * Verify that given address is the address of an attached segment.
 * Return 1 if address is valid; 0 if not.
 */
static int
good_addr(address)
char *address;
{
	register struct state	*p; /* ptr to state of attached segment */
	for(p=ap; p!=&ap[nap]; p++)
		if(p->shmaddr==address)
			return 1;
	return 0;
}
