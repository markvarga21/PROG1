#include <stdio.h>

void my_function(char* p, int x)
{
	printf("p is %s and x is %d\n", p, x);
}

int main()
{
	// 1-es feladat
	printf("1-es feladat: \n");
	printf("Hello World!\n\n");

	// 2-es feladat
	printf("2-es feladat: \n");
	char* hello = "Hello";
	char* world = "World!";
	printf("%s %s\n\n", hello, world);

	// 3-as feladat
	printf("3-as feladat: \n");
	my_function("foo", 7);
	my_function("alma", 200);
	my_function("korte", -5);
	return 0;
}