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
};

void t_option_i(struct test t)
{
	char **argv = ft_strsplit(t.argv_str, " ");

	t_env_ret ret = { .argv = argv };

	int result_int = option_i(&ret);

	if (test_cmp_int(t.expect_int, result_int)
		|| test_cmp_split_str("env diff", t.expect_env, ret.env)
		|| test_cmp_split_str("argv diff", t.expect_argv, ret.argv))
		log_test_line(1, t.line_nb)


	ft_strsplit_free(&argv);
	ft_strsplit_free(&ret.env);
}

void test_main_env()
{
	/*
	* test option -i
	* */
	{
		// test no value
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "",

			.expect_argv = "",
			.expect_env = "",
			.expect_int = OK
		});

		// test value no key
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "ar_1",

			.expect_argv = "ar_1",
			.expect_env = "",
			.expect_int = OK
		});

		// test one key
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "ar_1=1",

			.expect_argv = "",
			.expect_env = "ar_1=1",
			.expect_int = OK
		});

		// test one 4
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "ar_1=1 ar_2=2 ar_3=3 ar_4=4",

			.expect_argv = "",
			.expect_env = "ar_1=1 ar_2=2 ar_3=3 ar_4=4",
			.expect_int = OK
		});

		// test one 4 one double
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "ar_1=1 ar_2=2 ar_3=3 ar_1=4",

			.expect_argv = "",
			.expect_env = "ar_2=2 ar_3=3 ar_1=4",
			.expect_int = OK
		});

		// test one 4 one double and stop
		t_option_i((struct test){ .line_nb = L,
			.argv_str = "ar_1=1 ar_2=2 ar_3=3 ar_1=4 ls -r",

			.expect_argv = "ls -r",
			.expect_env = "ar_2=2 ar_3=3 ar_1=4",
			.expect_int = OK
		});
	}
}


