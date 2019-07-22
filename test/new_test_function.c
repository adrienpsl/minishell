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
