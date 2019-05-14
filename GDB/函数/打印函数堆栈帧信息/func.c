#include <stdio.h>
int func(int a, int b)
{
	int c = a * b;
	printf("c is %d\n", c);
}

int main(void) 
{
	func(1, 2);
	return 0;
}