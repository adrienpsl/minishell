
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
	ret = ms_env();

	// print error
	if (
	 ft_strsplit_cmp(tSplit.env_tmp, g_ms.env_tmp) ||
	 ft_strsplit_cmp(tSplit.argv_end, g_ms.argv) ||
	 !ft_streq(test.print, g_test_buffer) ||
	 ret != test.ret_int
	 )
	{
		printf("ms env %d \n", test.nb_test);

		ft_test_ifcmp_printsplit(tSplit.env_tmp, g_ms.env_tmp);
		ft_test_ifcmp_printsplit(tSplit.argv_end, g_ms.argv);
		ft_test_if_streq(test.print, g_test_buffer);
		if (ret != test.ret_int)
			printf("ret diff %d // %d \n", test.ret_int, ret);
	}

	// free
	ms_free(g_ms.env);
	ms_free(g_ms.env_tmp);
	test_free(&tSplit);
}


void new_test_all()
{
	g_test = 1;
	new_passed_test();

	// test env null
//	test_ms_env((ms_test) {
//	 .nb_test = 19,
//	 .env = "a1=toto a2=titi a3=tata",
//	 .argv_end = "",
//	 .env_tmp = "",
//	 .argv = "",
//	 .print = "a1=toto\na2=titi\na3=tata\n",
//	 .ret_int = 0
//	});

	// test env -i
	test_ms_env((ms_test) {
	 .nb_test = 20,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv_end = "",
	 .env_tmp = "",
	 .argv = "-i",
	 .print = "\n",
	 .ret_int = 0
	});


	// test env -u --

	// test env --

	// test -i toto >

	// test -u exist

	// test -u not exist


}