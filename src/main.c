#include <stdio.h>
#include <minishell.h>

void init(char **env)
{
	ft_bzero(&g_ms, sizeof(g_ms));
	ms_env_copy(env);
	g_ms.buffer = g_ms.buffer_array;
	signal(SIGINT, signal_minishell);
//	ms_loop();
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	init(env);

	test_all(env);

//	ms_loop();
	//	ft_str_split_free(&g_ms.env);

	return (0);
}