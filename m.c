#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	fprintf(stderr, "Pid: %i\n", getpid());
	while(1) sleep(10);
	return (0);
}
