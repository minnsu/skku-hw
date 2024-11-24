#include <stdio.h>

int main(){
	int i = 21;
	int j = 0;
	while(i--){
		// scanf("%d", &j);
        printf("%d\n", j + 1);
		sleep(1);
	}
	return 0;
}
