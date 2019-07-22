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
	ft_bzero(split, sizeof(t_split));
	if (test->env)
		split->env = ft_strsplit(test->env, " ");
	if (test->argv)
		split->argv = ft_strsplit(test->argv, " ");
	if (test->new_env)
		split->new_env = ft_strsplit(test->new_env, " ");
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



void test_ms_env_add(ms_test test)
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
	ret = ms_setenv();

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
void test_ms_unsetenv(ms_test test)
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

/* all test passed ------------------------------------------------------------ */
void new_passed_test()
{
	test_ms_init((ms_test) {
	 .env = "toto=titi"
	});

	char *env_star = "toto=titi";
	(void) env_star;


	// too much argv
	test_ms_env_add((ms_test) {
	 .nb_test = 0,
	 .env = env_star,
	 .argv = "titi tata toto",
	 .print = MS_BAD_NB_ARG"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});
	// no argv
	test_ms_env_add((ms_test) {
	 .nb_test = 1,
	 .env = env_star,
	 .argv = "",
	 .print = MS_BAD_NB_ARG"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	//	 forbidden char
	test_ms_env_add((ms_test) {
	 .nb_test = 2,
	 .env = env_star,
	 .argv = "toto titi$",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 3,
	 .env = env_star,
	 .argv = "toto$titi",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 4,
	 .env = env_star,
	 .argv = "toto= titi",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 5,
	 .env = env_star,
	 .argv = "toto ti=ti",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 6,
	 .env = env_star,
	 .new_env = env_star,
	 .argv = "toto=titi=",
	 .print = MS_SETENV_FORBIDDEN_CHAR"\n",
	 .ret_int = -1
	});

	// test max env, check than MS_SIZE_MAX_ENV Will be 4
	test_ms_env_add((ms_test) {
	 .nb_test = 7,
	 .env = "toto=fil tata=titi super=manger faire=chips",
	 .new_env = "toto=fil tata=titi super=manger faire=chips",
	 .argv = "toata titi",
	 .print = MS_NEW_ENV_TOO_BIG"\n",
	 .ret_int = -1
	});

	// good and add
	char *full_env = "a1=toto a2=titi a3=tata";
	test_ms_env_add((ms_test) {
	 .nb_test = 8,
	 .env = full_env,
	 .new_env = "a1=toto a2=titi a3=tata new=add",
	 .argv = "new=add",
	 .print = "",
	 .ret_int = 0
	});

	// good and replace
	test_ms_env_add((ms_test) {
	 .nb_test = 9,
	 .env = "a1=toto a2=titi a3=tata",
	 .new_env = "a2=titi a3=tata a1=lalala",
	 .argv = "a1=lalala",
	 .print = "",
	 .ret_int = 0
	});

	test_ms_env_add((ms_test) {
	 .nb_test = 10,
	 .env = "a1=toto a2=titi a3=tata",
	 .new_env = "a1=toto a2=titi a3=hohoho",
	 .argv = "a3=hohoho",
	 .print = "",
	 .ret_int = 0
	});

	/* unsetenv ------------------------------------------------------------ */
	// to much argv
	test_ms_unsetenv((ms_test) {
	 .nb_test = 11,
	 .env = "",
	 .argv = "titi tata toto",
	 .print = MS_BAD_NB_ARG"\n",
	 .new_env = "",
	 .ret_int = -1
	});

	// few argv
	test_ms_unsetenv((ms_test) {
	 .nb_test = 12,
	 .env = "",
	 .argv = "",
	 .print = MS_BAD_NB_ARG"\n",
	 .new_env = "",
	 .ret_int = -1
	});

	// key not in env
	test_ms_unsetenv((ms_test) {
	 .nb_test = 13,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a",
	 .print = "",
	 .new_env = "a1=toto a2=titi a3=tata",
	 .ret_int = 0
	});

	// same
	test_ms_unsetenv((ms_test) {
	 .nb_test = 14,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "toto",
	 .print = "",
	 .new_env = "a1=toto a2=titi a3=tata",
	 .ret_int = 0
	});

	// delete first
	test_ms_unsetenv((ms_test) {
	 .nb_test = 15,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a1",
	 .print = "",
	 .new_env = "a2=titi a3=tata",
	 .ret_int = 0
	});

	// middle
	test_ms_unsetenv((ms_test) {
	 .nb_test = 16,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a2",
	 .print = "",
	 .new_env = "a1=toto a3=tata",
	 .ret_int = 0
	});

	// end
	test_ms_unsetenv((ms_test) {
	 .nb_test = 17,
	 .env = "a1=toto a2=titi a3=tata",
	 .argv = "a3",
	 .print = "",
	 .new_env = "a1=toto a2=titi",
	 .ret_int = 0
	});

	// one
	test_ms_unsetenv((ms_test) {
	 .nb_test = 18,
	 .env = "a1=toto",
	 .argv = "a1",
	 .print = "",
	 .new_env = "",
	 .ret_int = 0
	});
}
