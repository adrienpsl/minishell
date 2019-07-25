#include <stdio.h>
#include <minishell.h>

void init(char **env)
{
	ft_bzero(&g_ms, sizeof(g_ms));
	ms_env_copy(env);
	signal(SIGINT, signal_minishell);
	ms_loop();
}

int ms_init(char **env)
{

	ft_bzero(&g_ms, sizeof(t_ms));
	g_ms.argv = (char **) g_ms.data.argv;
	ft_bzero(g_ms.argv, (40000) * sizeof(char **));

	g_ms.env = (char **) g_ms.data.env;
	ft_bzero(g_ms.env, (MS_SIZE_MAX_ENV + 1) * sizeof(char **));

	g_ms.env_tmp = (char **) g_ms.data.env_tmp;
	ft_bzero(g_ms.env_tmp, (MS_SIZE_MAX_ENV + 1) * sizeof(char **));

	if (!(g_ms.env = ft_strsplit_copy(env, 0)))
		return (-1);
	return (0);
}

void ms_free(char **env)
{
	while (*env)
	{
		free(*env);
		env++;
	}
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