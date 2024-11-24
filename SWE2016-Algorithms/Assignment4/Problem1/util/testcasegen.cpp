#include <cstdlib>
#include <cstdio>
#include <random>

int main(int argc, char** argv){
	FILE *fw = fopen(argv[1], "w");
	int n, m;
	printf("Enter first line { } { } \n=> ");
	scanf("%d %d", &n, &m);
	fprintf(fw, "%d %d\n", n, m);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, n);
	std::uniform_int_distribution<int> op(0, 1);
	for(int i = 0; i < m; i++){
		fprintf(fw ,"%d %d %d\n", op(gen), dis(gen), dis(gen));
	}
	return 0;
}
