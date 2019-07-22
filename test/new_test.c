
#include <libft.h>
#include <minishell.h>
#include "test.h"
//#include "../src/main.c"

// utils
void test_free(t_split *split);
void test_do_split(ms_test *test, t_split *split);

// function
void test_ms_init(ms_test ms_test);

void test_env(ms_test test)
{
	t_split s;
	test_do_split(&test, &s);

	if (
	 !ft_test_streq(test.print, g_test_buffer)
	 )
	{
		ft_test_if_streq(test.print, g_test_buffer);
	}
	test_free(&s);
}


void test_ms_env_add(ms_test test)
{
	// init
	t_split s;
	test_do_split(&test, &s);

	// function tested
	ms_env_add(g_ms.env, test.new_var);

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
void new_test_all()
{
	/* init ms ------------------------------------------------------------ */
	// test init and free function
	test_ms_init((ms_test) {
	 .env = "toto=titi"
	});

	/* Env add ------------------------------------------------------------ */

	//	test_env((ms_test) {
	//	 .env = "",
	//	 .print ="",
	//	});
}
