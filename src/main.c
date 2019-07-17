#include <stdio.h>
#include <minishell.h>


int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	m.buffer = m.buffer_array;
	signal(SIGINT, signal_minishell);

//	test_all();
		ms_loop();

	return (0);
}