
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


void test_ms_init(ms_test test)
{
	// init
	t_split s;
	test_do_split(&test, &s);

	ms_init(s.env);

	if (ft_str_split_cmp(g_ms.env, s.env))
	{
		printf("Ms init %d \n", test.nb_test);
		ft_test_ifcmp_printsplit(g_ms.env, s.env);
	}

	// free
	ms_free(g_ms.env);
	test_free(&s);
}



// test init struct

// test delete struct

// test free my obj

void new_test_all()
{
	// test init and delete function
	test_ms_init((ms_test) {
	 .env = "toto=titi"
	});

	/* Env copy ------------------------------------------------------------ */

//	test_env((ms_test) {
//	 .env = "",
//	 .print ="",
//	});
}
