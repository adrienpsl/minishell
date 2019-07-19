#include <stdio.h>
#include <minishell.h>

void init(char **env)
{
	ft_bzero(&g_ms, sizeof(g_ms));
	ms_env_copy(env);
	signal(SIGINT, signal_minishell);
	ms_loop();
}


void init_ms(char **env)
{

}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	printf("%ld \n", sizeof(char **) * 40000);
	init(env);
//	test_all(env);

//	ft_strsplit_free(&g_ms.env);

//	ms_loop();
	//	ft_strsplit_free(&g_ms.env);
	while (1)
		;
	return (0);
}