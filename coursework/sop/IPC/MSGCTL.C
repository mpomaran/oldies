/* 
 * msgctl.c: illustrates the msgctl() function. It prompts for the arguments,
 * makes the call, and reports the results.
 * Based on the code in "SunOS 5.2 System Services"
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <time.h>
static void do_msgctl();
static char warning_msg[]="If you remove read permission for \
yourself, this program will fail freqeuntly!";

void main()
{
	struct msqid_ds buf;	/* queue descriptor buffer for IPC_STAT
				   and IP_SE commands */
	int	cmd,	/* command to be given to msgctl() */
		msqid;	/* queue ID to be given to msgctl() */

	(void) fprintf(stderr,
		"All numeric input is expected to follow C convenctions:\n");
	(void) fprintf(stderr,"\t0x... is interpreted as hexadecimal,\n");
	(void) fprintf(stderr,"\t0...  is interpreted as octal,\n");
	(void) fprintf(stderr,"\t0 otherwise, decimal\n");

/*
 * get the msqid and cmd arguments for the msgctl() call.
 */
	(void) fprintf(stderr,"Please enter arguments for the msgctl() call");
	(void) fprintf(stderr,"\nEnter the msqid: ");
	(void) scanf("%i",&msqid);
	(void) fprintf(stderr,"\nValid msgctl commands are:\n");
	(void) fprintf(stderr,"\tIPC_RMIDL= %d\n",IPC_RMID);
	(void) fprintf(stderr,"\tIPC_SET  = %d\n",IPC_SET);
	(void) fprintf(stderr,"\tIPC_STAT = %d\n",IPC_STAT);
	(void) fprintf(stderr,"\nEnter the value for the command: ");
	(void) scanf("%i",&cmd);
	switch(cmd){
	case IPC_SET:
/*
 * Modify settings in the message queue control structure.
 */
		(void) fprintf(stderr,"Before IPC_SET, get current values:");
/*
 * Fall through to IPC_STAT processing
 */
	case IPC_STAT:
/*
 * Get a copy of the current message queue control structure
 * and show it to the user
 */
		do_msgctl(msqid,IPC_STAT,&buf);
		(void) fprintf(stderr,"msg_perm.uid = %d\n",buf.msg_perm.uid);
		(void) fprintf(stderr,"msg_perm.gid = %d\n",buf.msg_perm.gid);
		(void) fprintf(stderr,"msg_perm.cuid= %d\n",buf.msg_perm.cuid);
		(void) fprintf(stderr,"msg_perm.cgid= %d\n",buf.msg_perm.cgid);
		(void) fprintf(stderr,"msg_perm.mode= %#o, ",buf.msg_perm.mode);
		(void) fprintf(stderr,
			"access permissions= %#o\n",buf.msg_perm.mode&0777);
		(void) fprintf(stderr,"msg_cbytes = %d\n",buf.msg_cbytes);
		(void) fprintf(stderr,"msg_qbytes = %d\n",buf.msg_qbytes);
		(void) fprintf(stderr,"msg_qnum   = %d\n",buf.msg_qnum);
		(void) fprintf(stderr,"msg_lspid  = %d\n",buf.msg_lspid);
		(void) fprintf(stderr,"msg_lrpid  = %d\n",buf.msg_lrpid);
		(void) fprintf(stderr,"msg_stime  = %s",buf.msg_stime ?
			ctime(&buf.msg_stime) : "Not Set\n");
		(void) fprintf(stderr,"msg_rtime  = %s",buf.msg_rtime ?
			ctime(&buf.msg_rtime) : "Not Set\n");
		(void) fprintf(stderr,"msg_ctime  = %s",ctime(&buf.msg_ctime));
		if(cmd==IPC_STAT) break;
/*
 * Now continue with IPC_SET
 */
		(void) fprintf(stderr,"Enter msg_perm.uid: ");
		(void) scanf("%hi",&buf.msg_perm.uid);
		(void) fprintf(stderr,"Enter msg_perm.gid: ");
		(void) scanf("%hi",&buf.msg_perm.gid);
		(void) fprintf(stderr,"%s\n",warning_msg);
		(void) fprintf(stderr,"Enter msg_perm.mode: ");
		(void) scanf("%hi",&buf.msg_perm.mode);
		(void) fprintf(stderr,"Enter msg_perm.qbytes: ");
		(void) scanf("%hi",&buf.msg_qbytes);
		do_msgctl(msqid,IPC_SET,&buf);
		break;
	case IPC_RMID:
	default:
/*
 * Remove the message queue or try an unknown command.
 */
		do_msgctl(msqid,cmd,(struct msqid_ds *)NULL);
		break;
	}
	exit(0);
	/*NOTREACHED*/
}
/*
 * Print indication of arguments being passed to msgctl(), call msgctl(),
 * and report the results.
 * If msgctl() fails, do not return; this exmple doesn't deal with errors,
 * it just reports them.
 */
static void
do_msgctl(msqid,cmd,buf)
struct msqid_ds *buf;	/* pointer to queue descriptor buffer */
int	cmd,	/* command code */
	msqid;	/* queue ID */
{
	register int rtrn;	/* hold area for return value from msgctl() */

	(void) fprintf(stderr,"\nmsgctl: Calling msgctl(%d,%d,%s)\n",
		msqid,cmd,buf? "&buf": "(struct msqid_ds *)NULL");
	rtrn=msgctl(msqid,cmd,buf);
	if(rtrn==-1){
		perror("msgctl: msgctl failed");
		exit(1);
		/*NOTREACHED*/
	} else {
		(void) fprintf(stderr,"msgctl: msgctl returned %d\n",rtrn);
	}
}
