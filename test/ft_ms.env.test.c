/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_test.h>
#include "../src/ft_ms.env.c"
#include "../src/ft_ms.env.set_unset.c"

struct test
{
	int line_nb;

	char *argv_str;
	int expect_int;
	char *env_str;

	char *value;
	char *key;
	char *variable;

	char *expect_print;
	char *expect_char;
	char *expect_argv;
	int expected_result_int;
};

/* ===== test env ================================================================ */

struct t_e
{
	t_env e;
	t_data d;
};

void t_option_i(struct test t)
{
	char **argv = ft_strsplit(t.argv_str, " ");
	char **argv_start = argv;

	t_env e;
	ft_bzero(&e, sizeof(t_env));
	int result_int = option_i(&argv, &e);

	if (test_cmp_int(t.expect_int, result_int)
		|| test_cmp_split_str("env diff ", t.expect_char, *get_env(&e))
		|| test_cmp_split_str("argv diff ", t.expect_argv, argv))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv_start);
	ft_strsplit_free(get_env(&e));
}

void t_option_u(struct test t)
{
	g_test = 1;
	t_env e;
	ft_bzero(&e, sizeof(t_env));

	e.env = ft_strsplit(t.env_str, " ");
	char **argv = ft_strsplit(t.argv_str, " ");
	char **argv_start = argv;

	int result_int = option_u(&argv, &e);

	if (test_cmp_int(t.expect_int, result_int)
		|| (t.expect_print && test_cmp_buff(t.expect_print))
		|| test_cmp_split_str("env diff ", t.expect_char, *get_env(&e))
		|| test_cmp_split_str("argv diff ", t.expect_argv, argv))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv_start);
	free_env(&e);
	g_test = 0;
}

void t_ms__env(struct test t)
{
	g_test = 1;
	t_env e;
	t_data d;
	ft_bzero(&e, sizeof(t_env));
	ft_bzero(&d, sizeof(t_data));

	d.argv = ft_strsplit(t.argv_str, " ");
	char **argv_start = d.argv;

	e.env = ft_strsplit(t.env_str, " ");

	int ret = ms__env(&d, &e);

	if (test_cmp_buff(t.expect_print))
		log_test_line(1, t.line_nb)

	if (
		test_cmp_int(t.expected_result_int, ret) ||
		test_cmp_split_str("env diff", t.expect_char, *get_env(&e)) ||
		test_cmp_split_str("argv diff", t.expect_argv, d.argv))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv_start);
	free_env(&e);
	g_test = 0;
}

void test_main_env()
{
	/*
	* test option -i
	* */
	{
		// test no value
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i",

			.expect_argv = "",
			.expect_char = "",
			.expect_int = OK
		});

		// test value no key
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1",

			.expect_argv = "ar_1",
			.expect_char = "",
			.expect_int = OK
		});

		// test one key
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1",

			.expect_argv = "",
			.expect_char = "ar_1=1",
			.expect_int = OK
		});

		// test one 4
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1 ar_2=2 ar_3=3 ar_4=4",

			.expect_argv = "",
			.expect_char = "ar_1=1 ar_2=2 ar_3=3 ar_4=4",
			.expect_int = OK
		});

		// test one 4 one double
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1 ar_2=2 ar_3=3 ar_1=4",

			.expect_argv = "",
			.expect_char = "ar_2=2 ar_3=3 ar_1=4",
			.expect_int = OK
		});

		// test one 4 one double and stop
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1 ar_2=2 ar_3=3 ar_1=4 ls -r",

			.expect_argv = "ls -r",
			.expect_char = "ar_2=2 ar_3=3 ar_1=4",
			.expect_int = OK
		});
	}

	/*
	* test option  -u
	* */
	{
		// no key
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u",
			.env_str = "a1",

			.expect_int = -1,
			.expect_argv = "",
			.expect_print = "env: option requires an argument -- u\n"
							"usage: env [-i] [name=value ...] [-u name]\n"
							"          [utility [argument ...]]\n",
			.expect_char = "a1"
		});

		// first good second bad
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u toto -u",
			.env_str = "toto=titi",

			.expect_int = -1,
			.expect_argv = "",
			.expect_print = "env: option requires an argument -- u\n"
							"usage: env [-i] [name=value ...] [-u name]\n"
							"          [utility [argument ...]]\n",
			.expect_char = "toto=titi"
		});

		// test good
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u toto",
			.env_str = "toto=titi",

			.expect_int = OK,
			.expect_argv = "",
			.expect_char = ""
		});

		// test hard
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u toto -u toto -u titi",
			.env_str = "toto=titi titi=flute aaa=ooo",

			.expect_int = OK,
			.expect_argv = "",
			.expect_char = "aaa=ooo"
		});

		// test hard
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u toto -u toto -u titi ls -aoe",
			.env_str = "toto=titi titi=flute aaa=ooo",

			.expect_int = OK,
			.expect_argv = "ls -aoe",
			.expect_char = "aaa=ooo"
		});
	}

	/*
	* test ms__env
	* */
	{
		// no argument
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "",
			.env_str = "toto=titi",

			.expect_argv = "",
			.expect_print = "toto=titi\n",
			.expected_result_int = OK,
			.expect_char = "toto=titi"
		});

		// no bad option
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-ps",
			.env_str = "toto=titi",

			.expect_argv = "-ps",
			.expect_print = "env: illegal option -- p\n"
							"usage: env [-i] [name=value ...] [-u name]\n"
							"          [utility [argument ...]]\n",
			.expected_result_int = -1,
			.expect_char = "toto=titi"
		});

		// no bad -u
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-u toto -u",
			.env_str = "toto=titi",

			.expect_argv = "",
			.expect_print = "env: option requires an argument -- u\n"
							"usage: env [-i] [name=value ...] [-u name]\n"
							"          [utility [argument ...]]\n",
			.expected_result_int = -1,
			.expect_char ="toto=titi"
		});

		// test i
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-i a=1 ,.poeuch=11239euo",
			.env_str = "toto=titi",

			.expect_argv = "",
			.expect_print = "a=1\n,.poeuch=11239euo\n",
			.expected_result_int = OK,
			.expect_char ="a=1 ,.poeuch=11239euo"
		});

		// test u
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-u a -u b",
			.env_str = "a=1 b=2 c=3",

			.expect_argv = "",
			.expect_print = "c=3\n",
			.expected_result_int = OK,
			.expect_char = "c=3"
		});

		// test -i arguments
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-i a=1 ,.poeuch=11239euo ls -r",
			.env_str = "toto=titi",

			.expect_argv = "ls -r",
			.expect_print = "",
			.expected_result_int = OK,
			.expect_char = "a=1 ,.poeuch=11239euo"
		});

		// test -u arguments
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-u a -u ,.poeuch=11239euo ls -r",
			.env_str = "a=1 b=2 c=3",

			.expect_argv = "ls -r",
			.expect_print = "",
			.expected_result_int = OK,
			.expect_char = "b=2 c=3"
		});
	}
}

/* ===== test utils ================================================================ */


void f_ms__env_add(struct test t)
{
	g_test = 1;
	// init
	char **env = ft_strsplit(t.env_str, " ");

	// do
	ms__env_add(&env, t.key, t.value, t.variable);

	// test
	ft_strsplit_print(env, ' ');
	if (test_cmp_buff(t.expect_char))
		log_test(1)

	// clean
	ft_strsplit_free(&env);
}

void f_ms__env_set(struct test t)
{
	g_test = 1;

	char **argv = ft_strsplit(t.argv_str, " ");
	char **env = ft_strsplit(t.env_str, " ");

	int ret = ms__setenv(argv, &env);

	if (test_cmp_int(t.expect_int, ret) ||
		test_cmp_buff(t.expect_print) ||
		test_cmp_split_str("env diff", t.expect_char, env))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv);
	ft_strsplit_free(&env);
}

void f_ms__unset_env(struct test t)
{
	g_test = 1;

	char **argv = ft_strsplit(t.argv_str, " ");
	char **env = ft_strsplit(t.env_str, " ");

	int ret = ms__unsetenv(argv, &env);

	if (test_cmp_int(t.expect_int, ret) ||
		test_cmp_buff(t.expect_print) ||
		test_cmp_split_str("env diff", t.expect_char, env))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv);
	ft_strsplit_free(&env);
}

void test_utils_env()
{
	/*
	* test ms__env_add
	* */
	{
		// test key null
		f_ms__env_add((struct test){
			.env_str = "val1=toto =error val2=titi val3=tata val4=tito",

			.expect_char = "val1=toto =error val2=titi val3=tata val4=tito"
		});

		// key + value, new variable
		f_ms__env_add((struct test){
			.env_str = "val1=toto =error val2=titi val3=tata val4=tito",
			.key = "minh", .value = "tresJolie",

			.expect_char = "val1=toto =error val2=titi val3=tata val4=tito minh=tresJolie"
		});

		// variable, new variable
		f_ms__env_add((struct test){
			.env_str = "val1=toto =error val2=titi val3=tata val4=tito",
			.variable = "minh=tresJolie",

			.expect_char = "val1=toto =error val2=titi val3=tata val4=tito minh=tresJolie"
		});

		// key + value, existing variable
		f_ms__env_add((struct test){
			.env_str = "val1=toto minh=toto =error val2=titi val3=tata val4=tito",
			.key = "minh", .value = "tresJolie",

			.expect_char = "val1=toto =error val2=titi val3=tata val4=tito minh=tresJolie"
		});

		// variable, existing variable
		f_ms__env_add((struct test){
			.env_str = "val1=toto minh=toto =error val2=titi val3=tata val4=tito",
			.variable = "minh=tresJolie",

			.expect_char = "val1=toto =error val2=titi val3=tata val4=tito minh=tresJolie"
		});
	}

	/*
	* test ms_env_set
	* */
	{
		// error : no argument
		f_ms__env_set((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "",

			.expect_print = MS__NAME"setenv: wrong arguments number\n",
			.expect_char = "a=1 b=2"
		});

		// to much argument
		f_ms__env_set((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "toto titi tata",

			.expect_print = MS__NAME"setenv: wrong arguments number\n",
			.expect_char = "a=1 b=2"
		});


		// one argument and no =
		f_ms__env_set((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "tototiti",

			.expect_print = MS__NAME"setenv: if one argv, must contain =\n",
			.expect_char = "a=1 b=2"
		});

		// one arguments
		f_ms__env_set((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "toto=titi",

			.expect_print = "",
			.expect_char = "a=1 b=2 toto=titi"
		});

		// 2 arguements
		f_ms__env_set((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "toto titi",

			.expect_print = "",
			.expect_char = "a=1 b=2 toto=titi"
		});
	}

	/*
	* test ms__unset_env
	* */
	{
		// no arguments
		f_ms__unset_env((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "",

			.expect_print = MS__NAME"unsetenv: wrong arguments number\n",
			.expect_char = "a=1 b=2"
		});

		// to munch arguments
		f_ms__unset_env((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "a a a ",

			.expect_print = MS__NAME"unsetenv: wrong arguments number\n",
			.expect_char = "a=1 b=2"
		});

		// delete one
		f_ms__unset_env((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "a",

			.expect_print = "",
			.expect_char = "b=2"
		});

		// delete is not in env
		f_ms__unset_env((struct test){ .line_nb = L,
			.env_str = "a=1 b=2",
			.argv_str = "au",

			.expect_print = "",
			.expect_char = "a=1 b=2"
		});
	}
}
