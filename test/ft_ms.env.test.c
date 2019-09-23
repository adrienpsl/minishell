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

struct test
{
	int line_nb;

	char *argv_str;
	int expect_int;
	char *env_str;

	char *expect_print;
	char *expect_env;
	char *expect_argv;
	int expected_result_int;
};

void t_option_i(struct test t)
{
	char **argv = ft_strsplit(t.argv_str, " ");
	char **argv_start = argv;

	char **new_env;
	int result_int = option_i(&argv, &new_env);

	if (test_cmp_int(t.expect_int, result_int)
		|| test_cmp_split_str("env diff ", t.expect_env, new_env)
		|| test_cmp_split_str("argv diff ", t.expect_argv, argv))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv_start);
	ft_strsplit_free(&new_env);
}

void t_option_u(struct test t)
{
	g_test = 1;
	char **env = ft_strsplit(t.env_str, " ");
	char **argv = ft_strsplit(t.argv_str, " ");
	char **argv_start = argv;

	char **new_env;
	int result_int = option_u(&argv, env, &new_env);

	if (test_cmp_int(t.expect_int, result_int)
		|| (t.expect_print && test_cmp_buff(t.expect_print))
		|| test_cmp_split_str("env diff ", t.expect_env, new_env)
		|| test_cmp_split_str("argv diff ", t.expect_argv, argv))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv_start);
	ft_strsplit_free(&new_env);
	ft_strsplit_free(&env);
	g_test = 0;
}

void t_ms__env(struct test t)
{
	g_test = 1;
	char **argv = ft_strsplit(t.argv_str, " ");
	char **argv_start = argv;
	char **env = ft_strsplit(t.env_str, " ");

	char **new_env = ms__env(&argv, env);

	if (test_cmp_buff(t.expect_print))
		log_test_line(1, t.line_nb)

	if (
		test_cmp_split_str("env diff", t.expect_env, new_env) ||
		test_cmp_split_str("argv diff", t.expect_argv, argv))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv_start);
	ft_strsplit_free(&new_env);
	ft_strsplit_free(&env);
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
			.expect_env = "",
			.expect_int = OK
		});

		// test value no key
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1",

			.expect_argv = "ar_1",
			.expect_env = "",
			.expect_int = OK
		});

		// test one key
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1",

			.expect_argv = "",
			.expect_env = "ar_1=1",
			.expect_int = OK
		});

		// test one 4
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1 ar_2=2 ar_3=3 ar_4=4",

			.expect_argv = "",
			.expect_env = "ar_1=1 ar_2=2 ar_3=3 ar_4=4",
			.expect_int = OK
		});

		// test one 4 one double
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1 ar_2=2 ar_3=3 ar_1=4",

			.expect_argv = "",
			.expect_env = "ar_2=2 ar_3=3 ar_1=4",
			.expect_int = OK
		});

		// test one 4 one double and stop
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "-i ar_1=1 ar_2=2 ar_3=3 ar_1=4 ls -r",

			.expect_argv = "ls -r",
			.expect_env = "ar_2=2 ar_3=3 ar_1=4",
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
			.expect_env = NULL
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
			.expect_env = NULL
		});

		// test good
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u toto",
			.env_str = "toto=titi",

			.expect_int = OK,
			.expect_argv = "",
			.expect_env = ""
		});

		// test hard
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u toto -u toto -u titi",
			.env_str = "toto=titi titi=flute aaa=ooo",

			.expect_int = OK,
			.expect_argv = "",
			.expect_env = "aaa=ooo"
		});

		// test hard
		t_option_u((struct test){ .line_nb = L,
			.argv_str = "-u toto -u toto -u titi ls -aoe",
			.env_str = "toto=titi titi=flute aaa=ooo",

			.expect_int = OK,
			.expect_argv = "ls -aoe",
			.expect_env = "aaa=ooo"
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
			.expected_result_int = -1,
			.expect_env = NULL
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
			.expect_env = NULL
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
			.expect_env = NULL
		});

		// test i
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-i a=1 ,.poeuch=11239euo",
			.env_str = "toto=titi",

			.expect_argv = "",
			.expect_print = "a=1\n,.poeuch=11239euo\n",
			.expected_result_int = -1,
			.expect_env = NULL
		});

		// test u
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-u a -u b",
			.env_str = "a=1 b=2 c=3",

			.expect_argv = "",
			.expect_print = "c=3\n",
			.expected_result_int = -1,
			.expect_env = NULL
		});

		// test -i arguments
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-i a=1 ,.poeuch=11239euo ls -r",
			.env_str = "toto=titi",

			.expect_argv = "ls -r",
			.expect_print = "",
			.expected_result_int = OK,
			.expect_env = "a=1 ,.poeuch=11239euo"
		});

		// test -u arguments
		t_ms__env((struct test){ .line_nb = L,
			.argv_str = "-u a -u ,.poeuch=11239euo ls -r",
			.env_str = "a=1 b=2 c=3",

			.expect_argv = "ls -r",
			.expect_print = "",
			.expected_result_int = OK,
			.expect_env = "b=2 c=3"
		});
	}
}


