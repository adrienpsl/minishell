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
#include <fcntl.h>
#include <sys/stat.h>
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
	ft_bzero(g_test_cd_buffer, 4000);
	ft_bzero(&m, sizeof(m));
	m.buffer = m.buffer_array;
	ms_env_copy(env);
	intern_ret = ft_cd(arg);
	if (ret != intern_ret
		|| (!ft_streq(curpath, g_test_cd_buffer))
		|| ft_str_split_cmp(new_env, m.env)
		|| !ft_streq(error_text, g_test_buffer))
	{
		printf("test ms cd : %d \n", test);
		if (ret != intern_ret)
			printf("retour res : %d , test: %d \n", ret, intern_ret);
		if (!ft_streq(curpath, g_test_cd_buffer))
		{
			printf("Error path \n");
			printf("res  path: %s \n", curpath);
			printf("test path: %s\n", g_test_cd_buffer);
		}
		if (ft_str_split_cmp(new_env, m.env))
			printf("split  env\n");
		if (!ft_streq(error_text, g_test_buffer))
		{
			printf("test : -%s-\n", error_text);
			printf("res  : -%s-\n", g_test_buffer);
		}
		printf("\n\n");
	}
}

void test_ms_env_copy(char **env, int ret, int error, int test)
{
	int intern_ret;
	ft_bzero(&m, sizeof(m));
	intern_ret = ms_env_copy(env);
	if (((m.env && !env) || (!m.env && env))
		|| ft_str_split_cmp(m.env, env)
		|| ret != intern_ret
		|| g_errno != error)
	{
		printf("error test : %d \n", test);
	}
	g_errno = 0;
	//	ft_strsplitprint_test(m.p_env);
}

void test_ms_env_add(char **env, char **new_var, int ret, char **res, char *str_error, int test)
{
	ft_bzero(g_test_buffer, 10000);
	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	int intern_ret;
	intern_ret = ft_setenv(new_var);
	if (((m.env && !env) || (!m.env && env))
		|| ft_str_split_cmp(m.env, res)
		|| ret != intern_ret
		|| !ft_streq(str_error, g_test_buffer))
	{
		printf("error m env add : %d \n", test);
		if (ft_str_split_cmp(m.env, res))
		{
			g_test = 0;
			ft_strsplitprint_test(m.env);
			ft_strsplitprint_test(m.env);
			printf("split error\n");
			g_test = 1;
		}
		if (ret != intern_ret)
			printf("ret error\n");
		if (!ft_streq(str_error, g_test_buffer))
		{
			printf("error error \n");
			printf("%s \n", g_test_buffer);
		}
		printf("------------ \n");
	}
}

void test_ms_env_remove(char **env,
 char *deleting_key, int ret, char **res, int error, int test)
{
	int intern_ret;

	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	intern_ret = ft_unsetenv(deleting_key);
	if (ft_str_split_cmp(m.env, res)
		|| ret != intern_ret
		|| error != g_errno)
	{
		printf("error test m env remove : %d \n", test);
		if (ft_str_split_cmp(m.env, res))
		{
			g_test = 0;
			ft_strsplitprint_test(m.env);
			ft_strsplitprint_test(m.env);
			printf("split error\n");
			g_test = 1;
		}
		if (ret != intern_ret)
			printf("ret error\n");
	}
	g_errno = 0;
}

void test_ms_get_env_value(char **env, char *key, char *ret, int test)
{
	char *intern_ret;

	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	intern_ret = ms_env_get_value(key);
	if (ret && intern_ret && !ft_streq(intern_ret, ret))
		printf("error test get value : %d \n", test);
	if ((!ret && intern_ret) || (ret && !intern_ret))
		printf("error test get value : %d \n", test);
}

void test_ms_env_modify(char **env, char *key, char *new_value, int ret, char **res, int test)
{
	int intern_ret;

	ft_bzero(&m, sizeof(m));
	ms_env_copy(env);
	intern_ret = ms_env_modify(key, new_value);
	if (ft_str_split_cmp(m.env, res)
		|| ret != intern_ret)
	{
		printf("error test env modify : %d \n", test);
		if (ft_str_split_cmp(m.env, res))
		{
			g_test = 0;
			ft_strsplitprint_test(m.env);
			printf("----------------------- \n");
			ft_strsplitprint_test(res);
			printf("split error\n");
			g_test = 1;
		}
		if (ret != intern_ret)
			printf("ret error\n");
	}
	g_errno = 0;
}

void test_quote(char *str, int res, int *test)
{
	int is_quote_ret;

	is_quote_ret = is_quote_paired(str);
	if (is_quote_ret != res)
	{
		printf("error print quote test %d res: %d \n", *test, is_quote_ret);
	}
	(*test)++;
}

void test_get_all_commands(char *name_file, char *res, int test)
{
	(void) name_file;
	char *ret = get_all_commands();
	if (!ft_streq(ret, ret))
	{
		printf("error test %d \n", test);
		printf("res : %s \n", res);
		printf("test : %s \n", ret);
	}
}

// write in my file and open fd
void write_in_file(char *str)
{
	int fd;
	chdir("/Users/adpusel/code/42/minishell");
	mkdir("test_files", 0777);
	fclose(fopen("test_files/current_test", "w"));
	fd = open("test_files/current_test", O_CREAT | O_RDWR);
	write(fd, str, strlen(str));
	g_fd = open("test_files/current_test", O_RDONLY);
}

void test_get_all_command(char *test_str, char *res, int *test)
{
	write_in_file(test_str);
	char *ret_str = get_all_commands();
	if (!ft_streq(ret_str, res))
	{
		printf("error get_all_command %d \n", *test);
		printf("res : %s \n", res);
		printf("test: %s \n", test_str);
	}
	(*test)++;
}
void transform_space(char *line);
void test_transform_space(char *str, char *res, int test)
{
	transform_space(str);
	if (!ft_streq(str, res))
	{
		printf("error transform space : %d \n", test);
		printf("res  :%s \n", res);
		printf("test :%s \n\n", str);
	}
}

void test_read_command(char *command, char *res, int test)
{
	write_in_file(command);
	char **ret_test = read_command();
	char **res_split = ft_str_split(res, ";");
	if (ft_str_split_cmp(ret_test, res_split))
	{
		printf("error test  read command: %d \n", test);
		ft_print_two_split(res_split, ret_test);
	}
}

void find_binary_test(char *name, char **env, char *res, int test)
{
	m.env = env;
	char *ret = ft_find_binary(name);
	if (!ft_streq(ret, res))
	{
		printf("error find binary test : %d \n", test);
		printf("res : %s \n", res);
		printf("test: %s \n", ret);
	}
}

void echo_test(char *line, char *res, int test)
{
	ft_bzero(g_test_buffer, 10000);
	write_in_file(line);
	char **argv = read_command();
	ft_echo(argv);
	char *buff = g_test_buffer;
	(void)buff;

	if (!ft_streq(g_test_buffer, res))
	{
		printf("error echo test %d \n", test);
		printf("res :-%s-", res);
		printf(" \n");
		printf("tes :-%s-", g_test_buffer);
		printf("\n--- \n");
	}
}
