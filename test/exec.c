#include <stdio.h>
#include <unistd.h>


int main(void)
{

	char *argv[] = {"/bin/ls", "-1", NULL};

	int val = execve(argv[0], argv, NULL);

	if (val == -1)
		perror("Error");

	printf("DONE with execute\n");

	return 0;

}

