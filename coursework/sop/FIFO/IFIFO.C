/* ififo.c
 * An example program that illustrates usage of interrupt-driven communication
 * through named pipes.
 * 26/XI/1995 - created by L.J. Opalski
 * 31/III/1998 - last modified (LJO)
 * It does not work under Linux
 */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
char *pname = "/tmp/fifo";
#define PERMISSIONS 0777
void cleanup(int sig), io_handler(int sig);
int fd;

void cleanup(sig)
int sig;
{
        unlink(pname);
        exit(0);
}

void io_handler(int sig){
	char buf[256];
	int i, len, nbytes;

	printf("ififo: signal nr %d received!\n",sig); fflush(stdout);
	nbytes=read(fd,&len,sizeof(int));
	if(nbytes<0){
		printf("\nnbytes=%d",nbytes);
		return;
	} else if(nbytes==0){
		return;
	}	
	if(len<=0){
		printf("\nlen=%d\n",len);
			return;
	}
	i=read(fd,buf,len);
	printf("%d bytes:%s\n",i,buf); fflush(stdout);
}

void main(argc,argv)
int argc;
char *argv[];
{
	int i;
#ifndef SIGSET
        struct sigaction vec;
#endif

	if(argc == 1){
	int flags;
/* Delete previous fifo file */
		unlink(pname);
                signal(SIGINT,cleanup);
                signal(SIGQUIT,cleanup);
                signal(SIGHUP,cleanup);
		setbuf(stdout,NULL); /* No buffering */
/* Create new named pipe with read/write permission for all users */
/*		if(mknod(pname,010777,0)){ */
		if(mknod(pname,S_IFIFO|PERMISSIONS,0)){
			perror("mknod() failed");
			exit(1);
		}
		for(i=0; i<20; i++){
			fd = open(pname,O_RDONLY|O_NDELAY);
			if(fd!=-1) break;
			if(errno!=ENXIO){
				perror("afifo waiting to open FIFO:");
				exit(1);
			} else {
				printf("waiting for a client");
				sleep(2);
			}
		}
#ifdef SIGSET
		sigset(SIGIO,io_handler);
#else
	        vec.sa_handler = io_handler;
		sigemptyset(&vec.sa_mask);
		vec.sa_flags = 0;
		if ( sigaction(SIGIO, &vec, NULL) == -1)
			perror(" sigaction(SIGIO)");
#endif
   /* Arrange for the current process to receive
    *  SIGIO when the state of the socket changes.
    *  Process group negative == deliver to process group.
    */
		if(fcntl(fd,F_SETOWN,-getpid())<0){
			perror("ififo:fcntl F_SETOWN");
			exit(1);
		}
		if((flags=fcntl(fd,F_GETFL,0))==-1){
			perror("ififo:fcntl F_GETFL");
			exit(1);
		}
/*		if((flags=fcntl(fd,F_SETFL,flags|FNDELAY|FASYNC))==-1){
		if((flags=fcntl(fd,F_SETFL,flags|FASYNC))==-1){
*/
		if((flags=fcntl(fd,F_SETFL,FASYNC))==-1){
			perror("ififo:fcntl F_SETFL, FNDELAY|FASYNC");
			exit(1);
		}

	}else{
		fd = open(pname,O_WRONLY);
	}
	if( fd<0 ){
		fprintf(stderr,"\nUnsuccessful open() of %s\n",pname);
		exit(1);
	} else
		printf("\nSuccessful open of %s\n",pname);
	if(argc >1){
		printf("\nargc=%d\n",argc);
		for(i=1; i<argc; i++){
		int len=strlen(argv[i])+1;
			printf("argv[%d]=%s, len=%d\n",i,argv[i],len);
			write(fd,&len,sizeof(int));
			write(fd,argv[i],len);
			printf("\nData sent!\n");
		}
		close(fd);/* Close the pipe */
		/* unlink(pname); *//* Delete fifo file */
	} else {
	fprintf(stderr,"\nLong sleep ...");
	sleep(1000);
	fprintf(stderr,"just has ended\nBye!\n");
	}
}
