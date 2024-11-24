#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv){
	FILE *fr1 = fopen(argv[1], "r");
	FILE *fr2 = fopen(argv[2], "r");
	char tmp1, tmp2;
	while(!feof(fr1) && !feof(fr2)){
		fscanf(fr1, "%c", &tmp1);
		fscanf(fr2, "%c", &tmp2);
		if(tmp1 != tmp2){
			printf("WRONG!\n");
			return 0;
		}
	}
	printf("CORRECT!\n");
	return 0;
}
