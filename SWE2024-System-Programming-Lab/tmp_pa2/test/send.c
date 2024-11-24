#include <stdio.h>

int main(){
	char tmp[16];
	int i = 20;
	while(i){
		printf("%d\n", i--);
		sleep(1);
	}
	return 0;
}