#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void get_flag(){
	int fd ;
	int password;
	int magic ;

	char key[] = "Ban_Ruo_Bo_Luo_Mi!";
	char cipher[] = {6, 14, 49, 6, 61, 0, 48, 19, 43, 4, 58, 19, 33, 7, 54, 62, 54, 102, 35, 12, 11, 96, 109, 74, 101};
	fd = open("/dev/urandom",0);
	read(fd,&password,4);
	printf("Give me maigc :");
	scanf("%d",&magic);
	if(password == magic){
		for(int i = 0 ; i < sizeof(cipher) ; i++){
			printf("%c",cipher[i]^key[i%strlen(key)]);
		}
	}
}

int main(){
	setvbuf(stdout,0,2,0);
	get_flag();
	return 0 ;
}
