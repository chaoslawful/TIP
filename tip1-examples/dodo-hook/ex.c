#include <stdio.h>

void g()
{
	printf("hello\n");
}

void f()
{
	g();
}

int main()
{
	f();
	return 0;
}

