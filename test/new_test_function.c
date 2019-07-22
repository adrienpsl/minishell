#include <libft.h>
#include <minishell.h>
#include "test.h"

/* test utils ------------------------------------------------------------ */
void test_free(t_split *split)
{
	if (split->env)
		ft_strsplit_free(&split->env);
	if (split->argv)
		ft_strsplit_free(&split->argv);
	if (split->new_env)
		ft_strsplit_free(&split->env);
}

void test_do_split(ms_test *test, t_split *split)
{
	if (test->env)
		split->env = ft_strsplit(test->env, " ");
	else
		split->env = NULL;
	if (test->argv)
		split->argv = ft_strsplit(test->argv, " ");
	else
		split->argv = NULL;
	if (test->new_env)
		split->new_env = ft_strsplit(test->new_env, " ");
	else
		split->new_env = NULL;
}

/* function ------------------------------------------------------------ */

void test_ms_init(ms_test test)
{
	// init
	t_split s;
	test_do_split(&test, &s);

	// function tested
	ms_init(s.env);

	// print error
	if (ft_strsplit_cmp(g_ms.env, s.env))
	{
		printf("Ms init %d \n", test.nb_test);
		ft_test_ifcmp_printsplit(g_ms.env, s.env);
	}

	// free
	ms_free(g_ms.env);
	test_free(&s);
}
