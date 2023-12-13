#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	printf("argc: $d\n, argc");

	for (int i = 0 ; argv[i]; i++)
		printf("argv[%d]: %s\n", i, argv[i]);

	return 0;
}
