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

#include <minishell.h>
#include "libft.h"

void test_get_env_variable(char *line, char **env, int end, char *res, int test)
{
	m.env = env;
	line = get_env_variable(line, end);
	if (!ft_streq(line, res))
	{
		printf("Error get_env_variable : %d \n", test);
		printf("res : %s \n", res);
		printf("ret : %s \n", line);
	}
}

void test_replace_env_variable(char *line, char **env, char *res, int test)
{
	m.env = env;
	line = replace_env_variable(ft_strdup(line));
	if (!ft_streq(line, res))
	{
		printf("Error repalace variable : %d \n", test);
		printf("res : %s \n", res);
		printf("ret : %s \n", line);
	}
}

void test_ms_cd(char **env, char **arg, char **new_env, int ret, char *curpath, char *error_text, int test)
{
	int intern_ret;
	t_ms *a = &m;
	(void) a;

	ft_bzero(g_test_buffer, 1000);
	ft_bzero(&m, sizeof(m));
	ft_bzero(m.testing_str, 10000);
	m.test = 1;
	m.buffer = m.buffer_array;
	ms_env_copy(env);
	m.arg = arg;
	intern_ret = ms_cd(arg);
	if (ret != intern_ret
		|| (curpath && !ft_streq(curpath, m.testing_str))
		|| ft_str_split_cmp(new_env, m.env)
		|| !ft_streq(error_text, g_test_buffer))
	{
		printf("test ms cd n : %d \n", test);
		if (ret != intern_ret)
			printf("retour res : %d , test: %d \n", ret, intern_ret);
		if ((curpath && !ft_streq(curpath, m.testing_str)))
		{
			printf("res  path: %s \n", curpath);
			printf("test path: %s\n", m.testing_str);
		}
		if (ft_str_split_cmp(new_env, m.env))
			printf("split  env\n");
		if (!ft_streq(error_text, g_test_buffer))
		{
			printf("test : %s \n", error_text);
			printf("res  : %s \n", g_test_buffer);
		}
		printf("\n");
	}
}