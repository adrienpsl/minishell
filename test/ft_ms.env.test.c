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

typedef struct ms_test
{
	int nb_test;
	int nb_line;
	char *str_argv;
	char *str_env;
	int result;
	char *result_env;
} ms_test;

int ms__env(t_array *argv, t_array *env);

static void test_function(ms_test test)
{
	char **env = ft_strsplit(test.str_env, " ");
	t_array *argv = ms__parse_str(test.str_argv, " ");
	ms__init(env);

	int ret;
	while ((ret = ms__env(argv, g_ms.env)));

	if (ret != test.result)
	{
		printf("return diff %d %d\n", test.result, ret);
		log_test_line(test.nb_test, test.nb_line)
	}

	if (ret == 1)
	{
		ftarray__func(g_ms.env_option, ms__print_env, NULL);
	}

	if (test_cmp_testbuff(test.result_env))
		log_test_line(test.nb_test, test.nb_line)

	ft_strsplit_free(&env);
	ms__free();
}

void test_ms__env()
{
	g_test = 1;

	// test with no argument
	test_function(
		(ms_test){ 0, L, "", "PATH=1 toto=titi", 0, "PATH=1\ntoto=titi\n" });

	// test
}