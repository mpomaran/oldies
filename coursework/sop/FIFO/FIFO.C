/* fifo.c
 * An example program that illustrates usage of named pipes, based on:
 * M.J. Bach, The Design of the UNIX Operating System, Prentice Hall, 1986.
 * Modified by L.J. Opalski (30/03/1998)
 */
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
char *pname = "/tmp/fifo";
#define PERMISSIONS 0777
void cleanup(int sig);

void cleanup(sig)
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

	if(argc == 1){/* Sender */
/* Delete previous fifo file */
		unlink(pname);
                signal(SIGINT,cleanup);
                signal(SIGQUIT,cleanup);
                signal(SIGHUP,cleanup);

/* Create new named pipe with read/write permission for all users */
		if(mknod(pname,S_IFIFO|PERMISSIONS,0)){
			perror("mknod() failed");
			exit(1);
		}
		fd = open(pname,O_RDONLY);
	}else{/* Recipient */
		fd = open(pname,O_WRONLY);
	}
	if( fd<0 ){
		fprintf(stderr,"\nUnsuccessful open() of %s\n",pname);
		exit(1);
	}else{
		printf("\nSuccessful open of %s\n",pname);
		fflush(stdout);
	}
	if(argc >1){/* Sender */
		printf("\nargc=%d\n",argc);
		for(i=1; i<argc; i++){
		int len=strlen(argv[i])+1;
			printf("argv[%d]=%s, len=%d\n",i,argv[i],len);
			write(fd,&len,sizeof(int));
			write(fd,argv[i],len);
		}
		close(fd);/* Close the pipe */
	}else{/* Recipient */
	   do{
	   int len, nbytes;
		
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
		i=read(fd,buf,len);
		printf("%d bytes:%s\n",i,buf);
		
	   }while(1);
	}
}
