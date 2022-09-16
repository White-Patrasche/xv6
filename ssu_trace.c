#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

#define MAXARG 100
int
main(int argc, char* argv[])
{
	int i;
	char *nargv[MAXARG];
	if(argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9')) {
		printf(1, "Useage : %s mask command\n", argv[0]);
		exit();
	}
	if(trace(atoi(argv[1])) < 0) {
		printf(1, "%s: trace failed\n", argv[0]);
		exit();
	}
	for(i = 2; i<argc && i < MAXARG; i++)
		nargv[i-2] = argv[i];
	exec(nargv[0],nargv);
	exit();
}
