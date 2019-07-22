
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
	t_split tSplit;
	int ret;

	ft_test_clear_testbuff();
	test_do_split(&test, &tSplit);
	ms_init(tSplit.env);

	// function tested
	g_ms.argv = tSplit.argv;
	g_ms.argv_size = ft_strsplit_count(g_ms.argv);
	ret = ms_set_env();

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
	/* init ms ------------------------------------------------------------ */
	// test init and free function
//	test_ms_init((ms_test) {
//	 .env = "toto=titi"
//	});

	/* Env add ------------------------------------------------------------ */
	char *env_star = "toto=titi";
	(void) env_star;


/*	// too much argv
	test_ms_env_add((ms_test) {
	 .nb_test = 0,
	 .env = env_star,
	 .argv = "titi tata toto",
	 .print = MS_SETENV_NB_ARGV"\n",
	 .new_env = env_star,
	 .ret_int = -1
	});
	// no argv
	test_ms_env_add((ms_test) {
	 .nb_test = 1,
	 .env = env_star,
	 .argv = "",
	 .print = MS_SETENV_NB_ARGV"\n",
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
	});*/

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


}