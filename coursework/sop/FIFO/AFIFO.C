/* afifo.c
 * An example program that illustrates usage of nonblocking named pipes.
 * 23/XI/1995 - created by L.J. Opalski
 * 30/III/1998 - last modified (LJO)
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
		for(i=0; i<20; i++){/* try 20 times */
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
		printf("Successful open() of %s\n",pname);
		fflush(stdout);
	}else{
		fd = open(pname,O_WRONLY);
	}
	if( fd<0 ){
		fprintf(stderr,"\nUnsuccessful open() of %s\n",pname);
		exit(1);
	}
	if(argc >1){
		printf("\nargc=%d\n",argc);
		for(i=1; i<argc; i++){
		int len=strlen(argv[i])+1;
			printf("argv[%d]=%s, len=%d\n",i,argv[i],len);
			write(fd,&len,sizeof(int));
			write(fd,argv[i],len);
		}
		close(fd);/* Close the pipe */
		/* unlink(pname); *//* Delete fifo file */
	}else{
	   do{
	   int len, nbytes;
		
		nbytes=read(fd,&len,sizeof(int));
		if(nbytes<0){
			printf("\nnbytes=%d",nbytes);
			break;
		} else if(nbytes==0){
			printf("sleeping ...\n"); sleep(2);
			continue;
		}	
		if(len<=0){
			printf("\nlen=%d\n",len);
				break;
		}
		i=read(fd,buf,len);
		printf("%d bytes:%s\n",i,buf);
		
	   }while(1);
	}
}
