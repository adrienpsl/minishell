
#include <libft.h>
#include <minishell.h>
#include "test.h"

void test_free(ms_test *test)
{
	if (test->split.argv)
		ft_strsplit_free(&test->split.argv);
	if (test->split.env)
		ft_strsplit_free(&test->split.env);
	if (test->split.new_env)
		ft_strsplit_free(&test->split.env);
}

void test_env(ms_test test)
{
	char **env = ft_str_split(test.env, " ");
	g_ms.env = env;

	if (
	 !ft_test_streq(test.print, g_test_buffer)
	 )
	{
		ft_test_if_streq(test.print, g_test_buffer);
	}

	test_free(&test);
}

// test init struct

// test delete struct

// test free my obj

void new_test_all()
{
	test_env((ms_test) {
	 .env = "",
	 .print ="",
	});
}
