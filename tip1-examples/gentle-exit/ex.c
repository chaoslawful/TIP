#include <stdio.h>
#include <unistd.h>

int g()
{
	sleep(10);
	return 10;
}

int f()
{
	int a=g();
	int b=a+1;
	return b;
}

int main()
{
	printf("%d\n", f());
	return 0;
}

