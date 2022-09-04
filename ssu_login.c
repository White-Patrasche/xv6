#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

#define LISTSIZE 16
#define IDLENGTH 32

char userID[16][32];
char pwdID[16][32];

char*argv[] = {"sh", 0};

void get_user_list() {
	int fd;
	fd = open("list.txt", O_RDONLY);

	if(fd < 0) {
		printf(1, "open error\n");
		exit();
	}
	
	//init userId, pwdId
	memset(userID, 0, sizeof(char)*LISTSIZE*IDLENGTH);
	memset(pwdID, 0, sizeof(char)*LISTSIZE*IDLENGTH);

	int userIdx = 0;

	char buf[1024];
	int n;
	
	if((n = read(fd, buf, sizeof(buf))) < 0) {
		printf(1, "read error\n");
		exit();
	}

	//read buffer one by one
	for(int i=0; i<n; i++) {
		for(int j=0; j<n-i; j++) {
			if(buf[j+i] != ' ') {
				userID[userIdx][j] = buf[j+i];
			} else {
				i += j + 1;
				break;
			}
		}
		for(int j=0; j<n-i; j++) {
			if(buf[j+i] != '\n') {
				pwdID[userIdx][j] = buf[j+i];
			} else {
				i += j;
				break;
			}
		}
		userIdx += 1;
	}
	close(fd);
}

int check_idpw() {
	char ID[100];
	char PW[100];
	printf(2, "Username: ");
	memset(ID, 0, sizeof(ID));
	gets(ID, sizeof(ID));

	printf(2, "Password: ");
	memset(PW, 0, sizeof(PW));
	gets(PW, sizeof(PW));

	//remove '\n'
	for(int i=0; i<100; i++) {
		if(ID[i] == '\n') {
			ID[i] = '\0';
			break;
		}
	}
	for(int i=0; i<100; i++) {
		if(PW[i] == '\n') {
			PW[i] = '\0';
			break;
		}
	}

	for(int i=0; i<LISTSIZE; i++) {
		//if user is valid
		if(!strcmp(userID[i], ID) && !strcmp(pwdID[i], PW)) {
			return 1;
		}
	}
	return 0;
}

int main() {
	get_user_list();
	if(check_idpw()) {
		exec("sh", argv);
	}
	exit();
}
