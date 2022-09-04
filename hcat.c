#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
int lines;

void
cat(int fd)
{
  int n;

  int count =0;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
	for(int i=0; i<n; i++) {
		write(1, buf+i, 1);
		if(buf[i] == '\n') {
			count += 1;
		}
		if(count >= lines) {
			exit();
		}
	}
  }

  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd;
  lines = atoi(argv[1]);

  if(argc <= 1){
    cat(0);
    exit();
  }
	
  if((fd = open(argv[2], 0)) < 0) {
	  printf(1, "cat: cannot open %s\n", argv[2]);
	  exit();
  }
  cat(fd);
  close(fd);
  exit();
}
