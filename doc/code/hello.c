#include <stdio.h>

int j;
int k = 0;

int main(void)
{
	int i;
	printf("The stack top is near %p\n", &i);
	printf("BSS %p\n", &j);
	printf("Data %p\n", &k);

	return 0;
}
