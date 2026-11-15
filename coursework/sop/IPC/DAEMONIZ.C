/*
 * Funkcja daemonize() powoduje przeksztalcenie procesu w demon
 * (w sensie UNIXa).
 *
 * Ostatnia modyfikacja: 11/10/1996 - L.J. Opalski
 */
#include <sys/resource.h> /* rlimit */

int daemonize(){
	int i, pid, size;
	struct rlimit rl;
	pid = fork();
	if (pid < 0) {
		perror("cannot fork");
		return -1;
	}
	if (pid)
		exit(0);
	rl.rlim_max = 0;
	getrlimit(RLIMIT_NOFILE, &rl);
	if ((size = rl.rlim_max) == 0)
		exit(1);
	for (i = 0; i < size; i++)
		(void) close(i);
	i = open("/dev/null", 2);
	if (i<0) return -2;
	if (dup2(i, 1)<0) return -3;
	if (dup2(i, 2)<0) return -4;
/* Zostan liderem sesji */
	setsid();
	if (chdir("/")<0) return -5;
	return 0;
}
