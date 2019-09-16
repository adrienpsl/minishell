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

#include <ft_test.h>
#include <minishell.prototypes.h>
#include "libft.h"

void test_init_g_ms(char *str);

typedef struct s
{
	int nb_test;
	int nb_line;

	char *env_str;
	char *str_argv;

	char *result_print;
	int result_int;
} t;

void static test_function(t t)
{
	g_test = 1;
	// init
	test_init_g_ms(t.env_str);
	char **argv = ft_strsplit(t.str_argv, " ");

	// call
	int ret = ms__cd(argv, g_ms.env, g_ms.buffer_cd);

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

void test__ms_cd()
{
	// test si avance bien le --
	test_function((t){
		.nb_test = 1,
		.nb_line = L,

		.str_argv = "-- ..",
		.env_str = "",

		.result_int = OK,
		.result_print = "",
	});

	// test print path with -
	test_function((t){
		.nb_test = 1,
		.nb_line = L,

		.str_argv = "-",
		.env_str = "OLDPATH=..",

		.result_int = OK,
		.result_print = "/Users/adpusel/code/42\n",
	});

	// test print path with 0
	test_function((t){
		.nb_test = 1,
		.nb_line = L,

		.str_argv = "",
		.env_str = "HOME=/ OLDPATH=..",

		.result_int = OK,
		.result_print = "",
	});

this not work !
	// test print path with arg arg
	test_function((t){
		.nb_test = 1,
		.nb_line = L,

		.str_argv = "/ /",
		.env_str = "OLDPATH=..",

		.result_int = OK,
		.result_print = "/Users/adpusel/code/42\n",
	});
}
