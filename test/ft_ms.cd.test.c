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
#include <../src/cd/ft_ms.cd.c>
#include <ft_test.h>

void test_one_and_zero_argv()
{
	g_test = 1;
	char **env = ft_strsplit("", " ");
	char *result;


	// test error HOME
	result = one_and_zero_argv(NULL, env);
	if (test_cmp_buff("minishell: line 26: cd: HOME not set\n")
		|| test_cmp_str(NULL, result))
		log_test(0)
	ftstr__free(&result);

	// test error OLDPATH
	result = one_and_zero_argv("-", env);
	if (test_cmp_buff("minishell: line 26: cd: OLDPATH not set\n")
		|| test_cmp_str(NULL, result))
		log_test(1)
	ftstr__free(&result);

	// test one simple argv
	result = one_and_zero_argv("toto", env);
	if (test_cmp_buff("")
		|| test_cmp_str("toto", result))
		log_test(2)
	ftstr__free(&result);


	// test with oldpath and home set
	env = ft_strsplit_add(env, "OLDPATH=minhestjolie", 1);
	result = one_and_zero_argv("-", env);
	if (test_cmp_buff("")
		|| test_cmp_str("minhestjolie", result))
		log_test(3)
	ftstr__free(&result);

	// test with oldpath and home set
	env = ft_strsplit_add(env, "HOME=minhjolie", 1);
	result = one_and_zero_argv(NULL, env);
	if (test_cmp_buff("")
		|| test_cmp_str("minhjolie", result))
		log_test(4)
	ftstr__free(&result);

	ft_strsplit_free(&env);
}

void test_two_argument()
{
	// test in path
	{
		char **argv = ft_strsplit("42 toto", " ");
		char *result = two_argument(argv);
		if (test_cmp_buff("")
			|| test_cmp_str(
			"/Users/adpusel/code/toto/minishell_new/cmake-build-debug", result))
			log_test(0)
		ftstr__free(&result);
		ft_strsplit_free(&argv);
	}

	// test start path
	{
		char **argv = ft_strsplit("/User toto", " ");
		char *result = two_argument(argv);
		if (test_cmp_buff("")
			|| test_cmp_str(
			"totos/adpusel/code/42/minishell_new/cmake-build-debug", result))
			log_test(0)
		ftstr__free(&result);
		ft_strsplit_free(&argv);
	}

	// test end path
	{
		char **argv = ft_strsplit("cmake-build-debug toto", " ");
		char *result = two_argument(argv);
		if (test_cmp_buff("")
			|| test_cmp_str(
			"/Users/adpusel/code/42/minishell_new/toto", result))
			log_test(0)
		ftstr__free(&result);
		ft_strsplit_free(&argv);
	}

	// not in path
	{
		char **argv = ft_strsplit("toto is_good", " ");
		char *result = two_argument(argv);
		if (test_cmp_buff("cd: string not in pwd: toto\n")
			|| test_cmp_str(
			NULL, result))
			log_test(0)
		ftstr__free(&result);
		ft_strsplit_free(&argv);
	}
}

void test_ms__cd()
{
	test_one_and_zero_argv();
	test_two_argument();
}