#include <stdio.h>
#include <minishell.h>

void init(char **env)
{
	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	m.buffer = m.buffer_array;
	signal(SIGINT, signal_minishell);
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	init(env);

	test_all();
//	ms_loop();
	//	ft_str_split_free(&m.env);

	return (0);
}