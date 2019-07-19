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

# include "../src/binary.c"
# include "../src/parser.c"
# include "../src/parser.read_full_line.c"

void test_get_env_variable(char *line, char **env, int end, char *res, int test)
{
	g_ms.env = env;
	line = ms_parser_find_$(line, end);
	if (!ft_streq(line, res))
	{
		printf("Error ms_parser_find_$ : %d \n", test);
		printf("res : %s \n", res);
		printf("ret : %s \n", line);
	}
}

void test_replace_env_variable(char *line, char **env, char *res, int test)
{
	g_ms.env = env;
	line = ms_parser_replace_$(ft_strdup(line));
	if (!ft_streq(line, res))
	{
		printf("Error repalace variable : %d \n", test);
		printf("res : %s \n", res);
		printf("ret : %s \n", line);
	}
	free(line);
}

void test_ms_cd(char **env, char **arg, char **new_env, int ret, char *curpath, char *error_text, int test)
{
	int intern_ret;
	t_ms *a = &g_ms;
	(void) a;

	ft_bzero(g_test_buffer, 1000);
	ft_bzero(g_mst.buffer, 4000);
	ft_bzero(&g_ms, sizeof(g_ms));
	ms_env_copy(env);
	intern_ret = ft_cd(arg);
	if (ret != intern_ret
		|| (!ft_streq(curpath, g_mst.buffer))
		|| ft_str_split_cmp(new_env, g_ms.env)
		|| !ft_streq(error_text, g_test_buffer))
	{
		printf("test g_ms cd : %d \n", test);
		if (ret != intern_ret)
			printf("retour res : %d , test: %d \n", ret, intern_ret);
		if (!ft_streq(curpath, g_mst.buffer))
		{
			printf("Error path \n");
			printf("res  path: %s \n", curpath);
			printf("test path: %s\n", g_mst.buffer);
		}
		if (ft_str_split_cmp(new_env, g_ms.env))
			printf("split  env\n");
		if (!ft_streq(error_text, g_test_buffer))
		{
			printf("test : -%s-\n", error_text);
			printf("res  : -%s-\n", g_test_buffer);
		}
		printf("\n\n");
	}
	ft_strsplit_free(&g_ms.env);
}

void test_ms_env_copy(char *env_str, int ret, int error, int test)
{
	ft_bzero(&g_ms, sizeof(g_ms));
	(void)error;

	char **env = ft_str_split(env_str, " ");
	int intern_ret = ms_env_copy(env);

	if (((g_ms.env && !env_str) || (!g_ms.env && env_str))
		|| ft_str_split_cmp(g_ms.env, env)
		|| ret != intern_ret)
	{
		printf("error test : %d \n", test);
	}
	ft_strsplit_free(&env);
	ft_strsplit_free(&g_ms.env);
}

void test_ms_env_add(char *env_str, char *test_str, int ret, char *res_str, char *error_str, int nb_test)
{
	// setup
	ft_bzero(g_test_buffer, 10000);
	ft_bzero(&g_ms, sizeof(g_ms));

	char **env = ft_str_split(env_str, " ");
	char **test = ft_str_split(test_str, " ");
	char **res = ft_str_split(res_str, " ");

	ms_env_copy(env);

	// test
	int intern_return = ft_setenv(test);
	ft_strsplit_free(&test);

	if (((g_ms.env && !env) || (!g_ms.env && env))
		|| ft_str_split_cmp(g_ms.env, res)
		|| ret != intern_return
		|| !ft_streq(error_str, g_test_buffer))
	{
		printf("error g_ms env add : %d \n", nb_test);
		if (ft_str_split_cmp(g_ms.env, res))
		{
			g_test = 0;
			ft_strsplitprint_test(g_ms.env);
			ft_strsplitprint_test(g_ms.env);
			printf("split error\n");
			g_test = 1;
		}
		if (ret != intern_return)
			printf("ret error\n");
		if (!ft_streq(error_str, g_test_buffer))
		{
			printf("error error \n");
			printf("%s \n", g_test_buffer);
		}
		printf("------------ \n");
	}
	ft_strsplit_free(&env);
	ft_strsplit_free(&res);
	ft_strsplit_free(&test);
	ft_strsplit_free(&g_ms.env);
}

void test_ms_env_remove(char *env_str,
 char *deleting_key, int ret, char *result_str, int error, int nb_test)
{
	(void)error;
	ft_bzero(&g_ms, sizeof(g_ms));
	ft_test_clear_testbuff();

	char **env = ft_str_split(env_str, " ");
	char **result = ft_str_split(result_str, " ");
	ms_env_copy(env);

	int intern_return = ft_unsetenv(deleting_key);

	if (ft_str_split_cmp(g_ms.env, result)
		|| ret != intern_return)
	{
		printf("error test g_ms env remove : %d \n", nb_test);
		ft_test_ifcmp_printsplit(result, g_ms.env);
		if (ret != intern_return)
			printf("ret error\n");
	}
	ft_strsplit_free(&g_ms.env);
	ft_strsplit_free(&env);
	ft_strsplit_free(&result);
}

void test_ms_get_env_value(char **env, char *key, char *ret, int test)
{
	char *intern_ret;

	ft_bzero(&g_ms, sizeof(g_ms));
	ms_env_copy(env);
	intern_ret = ms_env_get_value(key, g_ms.env);
	if (ret && intern_ret && !ft_streq(intern_ret, ret))
		printf("error test get value : %d \n", test);
	if ((!ret && intern_ret) || (ret && !intern_ret))
		printf("error test get value : %d \n", test);
	ft_strsplit_free(&g_ms.env);
}

void test_ms_env_modify(char **env, char *key, char *new_value, int ret, char **res, int test)
{
	int intern_ret;

	ft_bzero(&g_ms, sizeof(g_ms));
	ms_env_copy(env);
	intern_ret = ms_env_modify(key, new_value);
	if (ft_str_split_cmp(g_ms.env, res)
		|| ret != intern_ret)
	{
		printf("error test env modify : %d \n", test);
		if (ft_str_split_cmp(g_ms.env, res))
		{
			g_test = 0;
			ft_strsplitprint_test(g_ms.env);
			printf("----------------------- \n");
			ft_strsplitprint_test(res);
			printf("split error\n");
			g_test = 1;
		}
		if (ret != intern_ret)
			printf("ret error\n");
	}
	ft_strsplit_free(&g_ms.env);
}

void test_quote(char *str, int res, int *test)
{
	int is_quote_ret;

	is_quote_ret = ms_is_quote_match(str);
	if (is_quote_ret != res)
	{
		printf("error print quote test %d res: %d \n", *test, is_quote_ret);
	}
	(*test)++;
}

void test_get_all_commands(char *name_file, char *res, int test)
{
	(void) name_file;
	char *ret = ms_parser_get_commands();
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
	g_mst.fd = open("test_files/current_test", O_RDONLY);
}

void test_get_all_command(char *test_str, char *res, int *test)
{
	write_in_file(test_str);
	char *ret_str = ms_parser_get_commands();
	if (!ft_streq(ret_str, res))
	{
		printf("error get_all_command %d \n", *test);
		printf("res : %s \n", res);
		printf("test: %s \n", test_str);
	}
	(*test)++;
	free(ret_str);
}
void ms_parser_transform_space(char *line);
void test_transform_space(char *str, char *res, int test)
{
	ms_parser_transform_space(str);
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
	char **ret_test = ms_parser_read_command();
	char **res_split = ft_str_split(res, ";");
	if (ft_str_split_cmp(ret_test, res_split))
	{
		printf("error test  read command: %d \n", test);
		ft_print_two_split(res_split, ret_test);
	}
	ft_strsplit_free(&ret_test);
	ft_strsplit_free(&res_split);
}

void test_ms_loop_on_path_directory(int test, char **env, char *res, char *name)
{
	ft_bzero(g_ms.buffer, 4000);
	g_ms.env = env;
	ms_loop_on_path_directory(name);
	if (!ft_streq(g_ms.buffer, res))
	{
		printf("error ms loop on path directory : %d \n", test);
		printf("res : %s \n", res);
		printf("test: %s \n", g_ms.buffer);
	}
}

void echo_test(char *line, char *res, int test)
{
	ft_bzero(g_test_buffer, 10000);
	write_in_file(line);
	char **argv = ms_parser_read_command();
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
	ft_strsplit_free(&argv);
}

void test_ft_env(int nb_test, char *argument_str, char *env_str, char *res_env_str, char *print)
{
	(void) print;
	ft_test_clear_testbuff();

	char **env = ft_str_split(env_str, " ");
	char **argv = ft_str_split(argument_str, " ");
	char **res_env = ft_str_split(res_env_str, " ");
	g_ms.env = env;
	(void)nb_test;

//	ft_env(argv);

//	if (
//	 !ft_test_streq(print, g_test_buffer) ||
//	 ft_str_split_cmp(g_test_env, res_env)
//	 )
//	{
//		printf("test ft_env n %d /////////////////////////////////// \n", nb_test);
//		ft_test_ifcmp_printsplit(res_env, g_test_env);
//		ft_test_if_streq(print, g_test_buffer);
//	}

	ft_strsplit_free(&env);
	ft_strsplit_free(&argv);
	ft_strsplit_free(&res_env);
}


















