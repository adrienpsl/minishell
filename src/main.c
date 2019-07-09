#include <stdio.h>
#include <minishell.h>

// copie et parse evn

// I need to copy that all stuff inside my
// I will make a wrapper to create and free the env split
// how I will save the useful command inside my env : path and home
//

// TODO :  checx if there is an env

int main(int ac, char **av, char **env)
{
	if (env == NULL)
		return EXIT_FAILURE;

	(void) ac;
	(void) av;
	char buff[10000];
	ft_mem_zero(buff, 10000);
//	read(0, buff, 100);
//	printf("%s \n", buff);
	test_all();

//	char **p_env = env;

//	while (*p_env)
//	{
//		printf("%s \n", *p_env);
//		p_env++;
//	}

	return 0;
}