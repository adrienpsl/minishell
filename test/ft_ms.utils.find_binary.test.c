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
#include <minishell.defines.h>
#include <ft_test.h>
#include "libft.h"

static void test_function(int test_nb, int mode, char *binary_name, char *res)
{
	test_clear_testbuff();
	char **env = ft_strsplit(
		"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
		" ");
	ms__init(env);

	char *ret = ms__find_binary(g_ms.env, binary_name,
								g_ms.buffer,
								mode);
	if (
		res == NULL
		)
	{
		if (res != ret)
			log_test(test_nb)
	}
	else if (
		ft_str_cmp(res, ret)
		)
	{
		printf("%s \n", res);
		printf("%s \n", ret);
		log_test(test_nb)
	}

	ft_strsplit_free(&env);
	ms__free();
}

void test_ms__find_binary()
{
	g_test = 1;

	/*
	* test bad entries
	* */
	{
		// no PATH
		{
			test_clear_testbuff();
			char **env = ft_strsplit("noting=toto", " ");
			ms__init(env);

			char *ret = ms__find_binary(g_ms.env, "test", g_ms.buffer,
										MS__FIND_BINARY_COMPLETION);
			if (
				NULL != ret ||
				test_cmp_testbuff(MS__NAME"no env PATH\n")
				)
				log_test(1)

			ft_strsplit_free(&env);
			ms__free();
		}
	}
	g_test = 0;

	/*
	* test mode == find
	* */
	{
		// no binary
		{
			test_clear_testbuff();
			char **env = ft_strsplit(
				"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
				" ");
			ms__init(env);

			char *ret = ms__find_binary(g_ms.env, "toto", g_ms.buffer,
										MS__FIND_BINARY_SEARCH);
			if (
				NULL != ret
				)
				log_test(2)

			ft_strsplit_free(&env);
			ms__free();
		}

		// binary search test
		{
			test_clear_testbuff();
			char **env = ft_strsplit(
				"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
				" ");
			ms__init(env);

			char *ret = ms__find_binary(g_ms.env, "test", g_ms.buffer,
										MS__FIND_BINARY_SEARCH);
			if (
				ft_str_cmp(ret, "/bin/test")
				)
				log_test(2)

			ft_strsplit_free(&env);
			ms__free();
		}

		// binary search cd
		{
			test_clear_testbuff();
			char **env = ft_strsplit(
				"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
				" ");
			ms__init(env);

			char *ret = ms__find_binary(g_ms.env, "cd", g_ms.buffer,
										MS__FIND_BINARY_SEARCH);
			if (
				ft_str_cmp(ret, "/usr/bin/cd")
				)
				log_test(2)

			ft_strsplit_free(&env);
			ms__free();
		}

		// binary search mongodb
		{
			test_clear_testbuff();
			char **env = ft_strsplit(
				"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
				" ");
			ms__init(env);

			char *ret = ms__find_binary(g_ms.env, "mongod",
										g_ms.buffer,
										MS__FIND_BINARY_SEARCH);
			if (
				ft_str_cmp(ret, "/Users/adpusel/code/mongodb/bin/mongod")
				)
				log_test(2)

			ft_strsplit_free(&env);
			ms__free();
		}

		// binary search error mongoodb
		{
			test_clear_testbuff();
			char **env = ft_strsplit(
				"PATH=/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/.nvm/versions/node/v10.15.3/bin:/Users/adpusel/.yarn/bin:/Users/adpusel/.config/yarn/global/node_modules/.bin:/Users/adpusel/code/mongodb/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:~/.dotnet/tools",
				" ");
			ms__init(env);

			char *ret = ms__find_binary(g_ms.env, "mongoodb",
										g_ms.buffer,
										MS__FIND_BINARY_SEARCH);
			if (
				NULL != ret
				)
				log_test(2)

			ft_strsplit_free(&env);
			ms__free();
		}
	}

	/*
	* test mode == completion
	* */
	{
		// test with test
		test_function(0, MS__FIND_BINARY_COMPLETION, "tes", "test");

		// test no exist
		test_function(1, MS__FIND_BINARY_COMPLETION, "ttttt", NULL);

		// test double cd
		test_function(2, MS__FIND_BINARY_COMPLETION, "cdcd", NULL);
	}
}