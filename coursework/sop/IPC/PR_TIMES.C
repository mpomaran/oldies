/* pr_times.c
 * Created: MAY-15-1991 (LJO)
 * Last update: OCT-04-1995 (LJO)
 */
#include <stdio.h>
#ifdef RUSAGE
#include <sys/time.h>
#include <sys/resource.h>
#else
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>
#endif

void pr_times(fp,times1, times2)
FILE *fp;
unsigned long times1[3], times2[3];
{
	fprintf(fp,"\n*** System mode time= %ld ms",times2[0]-times1[0]);
	fprintf(fp,"\n*** User   mode time= %ld ms",times2[1]-times1[1]);
	fprintf(fp,"\n*** Elapsed     time= %ld ms\n",times2[2]-times1[2]);
	fflush(fp);
}/* pr_times */
/* -------------------------- */
void get_times(alltimes)
unsigned long alltimes[3];
{/* Reports time in milisecs */
#ifdef RUSAGE
  struct timeval tp;
  struct timezone tzp;
  struct rusage ru;

  extern int gettimeofday();

	getrusage(RUSAGE_SELF,&ru);
	gettimeofday(&tp,&tzp);

	alltimes[2] = tp.tv_sec*1000+tp.tv_usec/1000;
	alltimes[0]=(ru.ru_stime).tv_sec*1000+(ru.ru_stime).tv_usec/1000;
	alltimes[1]=(ru.ru_utime).tv_sec*1000+(ru.ru_utime).tv_usec/1000;
#else
    struct tms tmsbuf;

    alltimes[2]=(long)(((double) times(&tmsbuf) / HZ)*1000);
    alltimes[0]=(long)(((double) tmsbuf.tms_stime / HZ)*1000);
    alltimes[1]=(long)(((double) tmsbuf.tms_utime / HZ)*1000);
#endif
}/* get_times */
/* ---------------------------- */
