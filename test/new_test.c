
#include <libft.h>
#include <minishell.h>
#include "test.h"
//#include "../src/main.c"

// utils
void test_free(t_split *split);
void test_do_split(ms_test *test, t_split *split);
void new_passed_test();


void test_ms_env(ms_test test)
{
	// init
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	ms_init(tSplit.env);

	// function tested
	g_ms.argv = tSplit.argv;
	g_ms.argv_size = ft_strsplit_count(g_ms.argv);
	ret = ms_unsetenv();

	// print error
	if (
	 ft_strsplit_cmp(tSplit.new_env, g_ms.env) ||
	 !ft_streq(test.print, g_test_buffer) ||
	 ret != test.ret_int
	 )
	{
		printf("ms env add %d \n", test.nb_test);

		ft_test_ifcmp_printsplit(tSplit.new_env, g_ms.env);
		ft_test_if_streq(test.print, g_test_buffer);
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ms_free(g_ms.env);
	test_free(&tSplit);
}


void new_test_all()
{
	g_test = 1;
	new_passed_test();


}