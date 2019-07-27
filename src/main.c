#include <stdio.h>
#include <minishell.h>

void init(char **env)
{
	ms_env_copy(env);
	signal(SIGINT, signal_minishell);
	ms_loop();
}



void new_test_all();

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	//	printf("%ld \n", sizeof(char **) * 40000);
	//	ms_init(env);

	new_test_all();

	//	ms_free(g_ms.env);
	//	test_all(env);

	//	ft_strsplit_free(&g_ms.env);

	//	ms_loop();
	//	ft_strsplit_free(&g_ms.env);
	return (0);
}