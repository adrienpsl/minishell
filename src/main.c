#include <stdio.h>
#include <minishell.h>

void new_test_all();

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	g_fd = 0;
	//	printf("%ld \n", sizeof(char **) * 40000);
	//	ms_init(env);

	g_env = ft_strsplit_copy(env, 0);
//	ms_loop();
	new_test_all();

	//	ms_free(g_ms.env);
	//	test_all(env);

	//	ft_strsplit_free(&g_ms.env);

	//	ms_loop();
	//	ft_strsplit_free(&g_ms.env);
	return (0);
}