#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv){
	FILE *fw = fopen(argv[1], "w");
	printf("Enter first line { } { }\n=> ");
	int n, Goalhigh;
	scanf("%d %d", &n, &Goalhigh);
	fprintf(fw, "%d %d\n", n, Goalhigh);
	int x, y;
	for(int i = 0; i < n / 2; i++){
		fprintf(fw, "%d %d\n", i, i*2 + 2);
		fprintf(fw, "%d %d\n", i*2 + 2, i*2 + 2);
	}
	fclose(fw);
	return 0;
}
