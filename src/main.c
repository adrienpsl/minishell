#include <stdio.h>
#include <minishell.h>

// copie et parse evn

// I need to copy that all stuff inside my
// I will make a wrapper to create and free the env split
// how I will save the useful command inside my env : path and home
//


// utiliser execve
// cette command va dans le
// donc je vais utiliser fork pour faire le travail mon gars

int main(int ac, char **av, char **env)
{
	if (env == NULL)
		return EXIT_FAILURE;

	(void) ac;
	(void) av;
	test_all();
//	char *toto[2] = { "/" };
//	pid_t father;
//	(void)father;
//
//	while(1)
//	{
//		father = fork();
//		if (father > 0)
//		{
//			wait(NULL);
//			printf("father \n");
//		}
//		if (father == 0)
//		{
//			printf("processs \n");
//			execve("/bin/ls", toto, NULL);
//		}
//	}
	return 0;
}