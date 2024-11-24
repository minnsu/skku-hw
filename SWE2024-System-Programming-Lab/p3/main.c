#include <stdio.h>

extern int plus(int a, int b);
extern int minus(int a, int b);

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d %d\n", plus(a, b), minus(a, b));
	return 0;
}
