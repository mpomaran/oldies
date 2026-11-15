/* sfifo.c
 * An example program that illustrates usage of select() with named pipes.
 * 23/XI/1995 - created by L.J. Opalski
 * 31/III/1998 - last modified (LJO)
 */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>

char *pname = "/tmp/fifo";
#define PERMISSIONS 0777
#define TIMEOUT 20
void clean(int sig);

void clean(sig)
int sig;
{
        unlink(pname);
        exit(0);
}

void main(argc,argv)
int argc;
char *argv[];
{

	int fd, i;
	char buf[256];

	if(argc == 1){
/* Delete previous fifo file */
		unlink(pname);
                signal(SIGINT,clean);
                signal(SIGQUIT,clean);
                signal(SIGHUP,clean);
/* Create new named pipe with read/write permission for all users */
		if(mknod(pname,S_IFIFO|PERMISSIONS,0)){
			perror("mknod() failed");
			exit(1);
		}
		for(i=0; i<20; i++){
			fd = open(pname,O_RDWR);
			if(fd!=-1) break;
			if(errno!=ENXIO){
				perror("afifo waiting to open FIFO:");
				exit(1);
			} else {
				printf("waiting for a client");
				sleep(2);
			}
		}
	}else{
		fd = open(pname,O_WRONLY);
	}
	if( fd<0 ){
		fprintf(stderr,"\nUnsuccessful open() of %s\n",pname);
		exit(1);
	}
        printf("Successful open() of %s\n",pname);
        fflush(stdout);
	if(argc >1){
		printf("\nargc=%d",argc);
		for(i=1; i<argc; i++){
		int len=strlen(argv[i])+1;
			printf("\nargv[%d]=%s, len=%d",i,argv[i],len);
			write(fd,&len,sizeof(int));
			write(fd,argv[i],len);
		}
		printf("\n");
		close(fd);/* Close the pipe */
	}else{
	   while(1){
		int in, numfds;
		struct fd_set readmask;
		struct timeval timeout;
		int len, nbytes;
	/*  setup the masks */
		FD_ZERO(&readmask);
		FD_SET(fd, &readmask);
		FD_SET(0, &readmask);
       /*  set the timeout value  */
		timeout.tv_sec = TIMEOUT; timeout.tv_usec = 0;
        /*  select on socket descriptors */
		if ((numfds = select(fd + 1, &readmask, NULL, NULL,
			 &timeout))  < 0) {
			perror("select failed "); exit(1);
		}
	        if (numfds == 0) {
   	fprintf(stderr,"No input for the last %d seconds\n",TIMEOUT);
			continue;
       		}
		if(FD_ISSET(fd,&readmask)){
			in=fd;
			printf("\nreading from the pipe...\n");
			nbytes=read(fd,&len,sizeof(int));
			if(nbytes<0){
				printf("\nnbytes=%d",nbytes);
				break;
			} else if(nbytes==0){
				continue;
			}	
			if(len<=0){
				printf("\nlen=%d\n",len);
				break;
			}
		}else if(FD_ISSET(0,&readmask)){
			in=0;
			len=sizeof(buf)-1;
			printf("\nreading from the stdin...\n");
		}else
			continue;
		i=read(in,buf,len);
		if(i<0){
			perror("read error");
			break;
		}
		buf[i]='\0';
		printf("%d bytes:%s\n",i,buf);
	   }
	}
}
