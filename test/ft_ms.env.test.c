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
#include "libft.h"
#include "../src/env/ft_ms.env.c"

typedef struct s
{
	char *argv_string;
	char *env_string;
	//
	int result_int;
	char *result_env_string;
	char *result_argv_string;
} t;

// check le return
// check argv good place
// check env_tmp good

void test_cmp_split(char *name, char *expected, char **returned)
{
	g_test = 1;
	test_clear_testbuff();
	ft_strsplit_print(returned, '\n');

	if (test_cmp_testbuff(expected))
	{
		printf("%s", name);
	}
	g_test = 0;
}

void test_env_option_i(t t)
{
	// function data
	char **argv_start = ft_strsplit(t.argv_string, " ");
	char **argv = argv_start;

	char **split_tmp =  ft_strsplit(t.env_string, " ");
	t_array *sys_env = ms__parse_env(split_tmp);
	ft_strsplit_free(&split_tmp);

	// return function
	int function_return;
	t_array *env_tmp = NULL;

	// function call
	function_return = option_i(&argv, &env_tmp);

	// function result test
	if (t.result_int != function_return)
	{
		printf("error return : \n");
		printf("expected : %d \n", t.result_int);
		printf("returned : %d \n", function_return);
	}
	// function argv forward test
	test_cmp_split("argv forward", t.result_argv_string, argv);
	// function test env
	test_cmp_split("env test", t.result_env_string, (char **)env_tmp->data);

	// free function data
	ft_strsplit_free(&argv_start);
	ftarray__free_func(&sys_env, ms__func_free_env, NULL);

	// free function created data
	if (env_tmp)
		ftarray__free_func(&env_tmp, ms__func_free_env, NULL);
}

void test_ms__env()
{
	/*
	* test env_option_i
	* */
	{
		// test with no param
		{
			test_env_option_i((t){
				.env_string = "PATH=super toto=titi Minh=jolie",
				.argv_string = "",
				.result_int = OK,
				.result_env_string = "",
				.result_argv_string = ""
			});
		}
	}
}