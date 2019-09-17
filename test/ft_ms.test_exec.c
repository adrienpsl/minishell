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

#include <minishell.prototypes.h>
#include <ft_test.h>
#include "libft.h"
# include "../src/ft_ms.exec.c"

void test_init_g_ms(char *str);

typedef struct s
{
	int nb_test;
	int nb_line;

	char *env_str;
	char *str_argv;

	char *result_print;
	char *result_char;
	int result_int;
} t;

void teste_function(t t)
{
	g_test = 1;
	// init
	test_clear_testbuff();
	test_init_g_ms(t.env_str);
	char **argv = ft_strsplit(t.str_argv, " ");

	// call
	int ret = ms__exec(argv, g_ms.env, g_ms.buffer_cd);

	// test
	if (test_cmp_int(t.result_int, ret))
		log_test_line(t.nb_test, t.nb_line)

	if (test_cmp_buff(t.result_print))
		log_test_line(t.nb_test, t.nb_line)

	// clean
	ms__free();
	ft_strsplit_free(&argv);
	g_test = 0;
}

void test_find_binary_path(t t)
{
	g_test = 1;
	// init
	test_clear_testbuff();
	test_init_g_ms(t.env_str);

	// call
	char *return_char = find_binary_path(t.str_argv, g_ms.env, g_ms.buffer_cd);

	// test
	if (test_cmp_str(t.result_char, return_char))
		log_test_line(t.nb_test, t.nb_line)

	if (test_cmp_buff(t.result_print))
		log_test_line(t.nb_test, t.nb_line)

	// clean
	ms__free();
	g_test = 0;
}

void test_ms__exec()
{
	// test / exist
	test_find_binary_path((t){ .nb_line = L,
		.str_argv = "/bin/ls",
		.env_str= "",

		.result_print ="",
		.result_char = "/bin/ls"
	});

	// test / no exist
	test_find_binary_path((t){ .nb_line = L,
		.str_argv = "/bin/l",
		.env_str= "",

		.result_print ="minishell: : no such file or directory: /bin/l\n",
		.result_char = NULL
	});

	// test / no right
	test_find_binary_path((t){ .nb_line = L,
		.str_argv = "/Users/adpusel/code/42/minishell/minishell_test",
		.env_str= "",

		.result_print ="minishell: : permission denied: /Users/adpusel/code/42/minishell/minishell_test\n",
		.result_char = NULL
	});

	// test command
	test_find_binary_path((t) {.nb_line = L,
		.str_argv = "ls",
		.env_str= "PATH=/bin:/",

		.result_print ="",
		.result_char = "/bin/ls"
	});

	// test command no exist
	test_find_binary_path((t) {.nb_line = L,
		.str_argv = "l",
		.env_str= "PATH=/bin:/",

		.result_print ="minishell:  command not found: l\n",
		.result_char = NULL
	});

	// test  no right
	test_find_binary_path((t) {.nb_line = L,
		.str_argv = "minishell_test",
		.env_str= "PATH=/bin:/:/Users/adpusel/code/42/minishell",

		.result_print ="minishell: : permission denied: minishell_test\n",
		.result_char = NULL
	});


}