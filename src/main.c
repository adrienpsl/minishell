#include <stdio.h>
#include <minishell.h>

void new_test_all();

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	ft_bzero(&g_ms, sizeof(t_ms));
	g_ms.env = ft_strsplit_copy(env, 0);


	g_ms.is_test = 1;
	new_test_all();


	//	if (!g_ms.is_test)
	//		ms_set_raw();
	//	ms_loop();

	return (0);
}