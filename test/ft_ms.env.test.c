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
	int print_env;
	int print_remaing_argv;
} ms_test;

int ms__env(t_array *argv, t_array *env);

static void test_function(ms_test test)
{
	char **env = ft_strsplit(test.str_env, " ");
	t_array *argv = ms__parse_str(test.str_argv, " ");
	ms__init(env);

	int ret;

	while ((ret = ms__env(argv, g_ms.env)))
	{
		if (OK == ft_str_cmp(get__argv_current(argv), "env"))
			argv->i += 1;
		else
			break;
	}

	if (ret != test.result)
	{
		printf("return diff %d %d\n", test.result, ret);
		log_test_line(test.nb_test, test.nb_line)
	}

	if (test.print_env)
		ftarray__func(g_ms.env_option, ms__print_env, NULL);

	if (test.print_remaing_argv)
		ft_strsplit_print(ftarray__current(argv), ' ');

	if (test_cmp_testbuff(test.result_env))
		log_test_line(test.nb_test, test.nb_line)


	ft_strsplit_free(&env);
	ms__free();
}

void test_ms__env()
{
	g_test = 1;

//	/*
	//	* test classic !
	//	* */
	//	{
	//		// test with no argument
	//		test_function(
	//			(ms_test){ 0, L, "", "PATH=1 toto=titi", 0,
	//					   "PATH=1\ntoto=titi\n", 0, 0 });
	//
	//		// test with env argument
	//		test_function(
	//			(ms_test){ 1, L, "env", "PATH=1 toto=titi", 0,
	//					   "PATH=1\ntoto=titi\n", 0, 0 });
	//
	//		// test with env argument
	//		test_function(
	//			(ms_test){ 2, L, "env ls", "PATH=1 toto=titi", 1,
	//					   "ls", 1, 1 });
	//
	//		// test with env env env env  argument
	//		test_function(
	//			(ms_test){ 3, L, "env env env env ls", "PATH=1 toto=titi", 1,
	//					   "ls", 1, 1 });
	//	}


	/*
	* test env -i
	* */
	test_function(
		(ms_test){ 4, L, "-i", "PATH=1 toto=titi", 0,
				   "", 0, 1 });
}