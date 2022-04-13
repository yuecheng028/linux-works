#include <stdio.h>

int add(int, int);

int main(void) {
	int x = 3;
	int y = 6;
	int z;

	z = add(x, y);
	
	printf("%d", z);

	return z;
}

int add(int a, int b) {
	return a + b;
}
