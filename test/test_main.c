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

#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

void test_ms_env_copy(char **env, int ret, int error, int test)
{
	int intern_ret;
	ft_bzero(&ms, sizeof(ms));
	intern_ret = ms_env_copy(env);
	if (((ms.env && !env) || (!ms.env && env))
		|| ft_str_split_cmp(ms.env, env)
		|| ret != intern_ret
		|| g_errno != error)
	{
		printf("error test : %d \n", test);
	}
	g_errno = 0;
	//	ft_str_split_print(ms.p_env);
}

void test_ms_env_add(char **env, char **new_var, int ret, char **res, char *str_error, int test)
{
	ft_bzero(g_test_buffer, 10000);
	ft_bzero(&ms, sizeof(ms));
	ms_env_copy(env);
	int intern_ret;
	intern_ret = ms_env_add(new_var);
	if (((ms.env && !env) || (!ms.env && env))
		|| ft_str_split_cmp(ms.env, res)
		|| ret != intern_ret
		|| !ft_streq(str_error, g_test_buffer))
	{
		printf("error ms env add : %d \n", test);
		if (ft_str_split_cmp(ms.env, res))
		{
			g_test = 0;
			ft_str_split_print(ms.env);
			ft_str_split_print(ms.env);
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

	ft_bzero(&ms, sizeof(ms));
	ms_env_copy(env);
	intern_ret = ms_env_remove(deleting_key);
	if (ft_str_split_cmp(ms.env, res)
		|| ret != intern_ret
		|| error != g_errno)
	{
		printf("error test ms env remove : %d \n", test);
		if (ft_str_split_cmp(ms.env, res))
		{
			g_test = 0;
			ft_str_split_print(ms.env);
			ft_str_split_print(ms.env);
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

	ft_bzero(&ms, sizeof(ms));
	ms_env_copy(env);
	intern_ret = env_get_value(key);
	if (ret && intern_ret && !ft_streq(intern_ret, ret))
		printf("error test get value : %d \n", test);
	if ((!ret && intern_ret) || (ret && !intern_ret))
		printf("error test get value : %d \n", test);
}

void test_ms_env_modify(char **env, char *key, char *new_value, int ret, char **res, int test)
{
	int intern_ret;

	ft_bzero(&ms, sizeof(ms));
	ms_env_copy(env);
	intern_ret = ms_env_modify(key, new_value);
	if (ft_str_split_cmp(ms.env, res)
		|| ret != intern_ret)
	{
		printf("error test env modify : %d \n", test);
		if (ft_str_split_cmp(ms.env, res))
		{
			g_test = 0;
			ft_str_split_print(ms.env);
			printf("----------------------- \n");
			ft_str_split_print(res);
			printf("split error\n");
			g_test = 1;
		}
		if (ret != intern_ret)
			printf("ret error\n");
	}
	g_errno = 0;
}

void test_ms_cd(char **env, char **arg, char **new_env, int ret, char *curpath, char *error_text, int test)
{
	int intern_ret;
	t_ms *a = &ms;
	(void) a;

	ft_bzero(g_test_buffer, 1000);
	ft_bzero(&ms, sizeof(ms));
	ft_bzero(ms.testing_str, 10000);
	ms.test = 1;
	ms.buffer = ms.buffer_array;
	ms_env_copy(env);
	ms.arg = arg;
	intern_ret = ms_cd(arg);
	if (ret != intern_ret
		|| (curpath && !ft_streq(curpath, ms.testing_str))
		|| ft_str_split_cmp(new_env, ms.env)
		|| !ft_streq(error_text, g_test_buffer))
	{
		printf("test n : %d \n", test);
		if (ret != intern_ret)
			printf("retour \n");
		if ((curpath && !ft_streq(curpath, ms.testing_str)))
		{
			printf("test path: %s\n", ms.testing_str);
			printf("res  path: %s \n", curpath);
		}
		if (ft_str_split_cmp(new_env, ms.env))
			printf("split  env\n");
		if (!ft_streq(error_text, g_test_buffer))
		{
			printf("test : %s \n", error_text);
			printf("res  : %s \n", g_test_buffer);
		}
	}
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
	if (!ft_streq(test_str, res))
	{
		printf("error get_all_command %d \n", *test);
		printf("res : %s \n", res);
		printf("test: %s \n", test_str);
	}
	(*test)++;
}

void test_transform_space(char *str, char *res, int test)
{
	char **argv = build_argv(str);
	if (!ft_streq(str, res))
	{
		printf("error transform space : %d \n", test);
		printf("res  :%s \n", res);
		printf("test :%s \n\n", str);
	}
	ft_str_split_print(argv);
	printf(" \n");
}

void tested_test()
{
	g_test = 1;

	char *test_1[1] = { NULL };
	test_ms_env_copy(test_1, 0, 0, 1);

	char *test_2[4] = { "toto=super", "mimi=toto", "superTest", NULL };
	test_ms_env_copy(test_2, 0, 0, 2);

	// test with var null && empty env
	char *env_3[2] = { NULL };
	char *newvar_3[3] = { NULL };
	test_ms_env_add(env_3, newvar_3, -1, NULL, "Bad number argument given to set env\n", 3);

	// test var null && 1 var env
	char *env_4[2] = { "toto=tata" };
	char *newvar_4[3] = { NULL };
	test_ms_env_add(env_4, newvar_4, -1, NULL, "Bad number argument given to set env\n", 4);

	// empty env
	char *env_5[2] = { NULL };
	char *res_5[2] = { "toto=tata" };
	char *newvar_5[2] = { "toto=tata" };
	test_ms_env_add(env_5, newvar_5, 0, res_5, "", 5);

	// bad variable : no =
	char *env_6[2] = { NULL };
	char *res_6[2] = { NULL };
	char *newvar_6[2] = { "tototata" };
	test_ms_env_add(env_6, newvar_6, -1, res_6, "The env separator is one single =\n", 6);

	// bad variable : too much =
	char *env_7[2] = { "tata=toto" };
	char *res_7[2] = { "tata=toto" };
	char *newvar_7[2] = { "toto=tata=" };
	test_ms_env_add(env_7, newvar_7, -1, res_7, "The env separator is one single =\n", 7);

	char *env_8[10] = { "tata=toto" };
	char *res_8[10] = { "tata=toto", "super=titi" };
	char *newvar_8[10] = { "super=titi", NULL };
	test_ms_env_add(env_8, newvar_8, 0, res_8, "", 8);

	// no env
	char *env_88[2] = { NULL };
	char *res_88[2] = { NULL };
	test_ms_env_remove(env_88, "toto", -1, res_88, 0, 88);

	// no key
	char *env_9[2] = { NULL };
	char *res_9[2] = { NULL };
	test_ms_env_remove(env_9, NULL, -1, res_9, 0, 9);

	// no key and env
	char *env_10[2] = { "toto=titi" };
	test_ms_env_remove(env_10, NULL, -1, env_10, 0, 10);

	// delete one
	char *env_11[2] = { "toto=tata" };
	char *res_11[2] = { NULL };
	test_ms_env_remove(env_11, "toto", 0, res_11, 0, 11);

	// delete middle
	char *env_12[5] = { "suer=aaoeu", "toto=tata", "manger=chipes", "aaaaaaa", NULL };
	char *res_12[5] = { "suer=aaoeu", "manger=chipes", "aaaaaaa", NULL };
	test_ms_env_remove(env_12, "toto", 0, res_12, 0, 12);

	// delete end
	char *env_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	char *res_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", NULL };
	test_ms_env_remove(env_13, "manger", 0, res_13, 0, 13);

	// no bad
	char *env_14[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_14, "mange", NULL, 14);

	// null key
	char *env_15[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_15, NULL, NULL, 15);

	// good key
	char *env_16[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_16, "suer", "aaoeu", 16);

	// good key
	char *env_17[5] = { "suer=aaoeu", "toto=", "aaaaaaa", "manger=chipes", NULL };
	test_ms_get_env_value(env_17, "toto", "", 17);

	//	test ms_env_modify
	char *env_117[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	char *res_117[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=titi", NULL };
	test_ms_env_modify(env_117, "manger", "titi", 0, res_117, 117);

	char *env_19[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *new_env_19[2] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	char *argv_19[3] = { "-", NULL };
	test_ms_cd(env_19, argv_19, new_env_19, 0, "/Users/adpusel", "", 19);

	char *env_20[3] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	char *argv_20[3] = { "--", "-", NULL };
	char *new_env_20[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_20, argv_20, new_env_20, 0, "/Users/adpusel/code/42/minishell/cmake-build-debug", "", 20);

	char *env_21[3] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	char *argv_21[3] = { "/Users/adpusel", NULL };
	char *new_env_21[2] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	test_ms_cd(env_21, argv_21, new_env_21, 0, "/Users/adpusel", "", 21);

	chdir("/Users/adpusel");
	char *env_22[3] = { "OLDPATH=/toto", NULL };
	char *argv_22[3] = { "--", "/Users/adpusel/code", NULL };
	char *new_env_22[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_22, argv_22, new_env_22, 0, "/Users/adpusel/code", "", 22);

	chdir("/Users/adpusel");
	char *env_23[3] = { "OLDPATH=/toto", NULL };
	char *argv_23[3] = { "--", "./code", NULL };
	char *new_env_23[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_23, argv_23, new_env_23, 0, "/Users/adpusel/./code", "", 23);

	chdir("/Users/adpusel");
	char *env_24[3] = { "OLDPATH=/toto", NULL };
	char *argv_24[3] = { "..", NULL };
	char *new_env_24[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_24, argv_24, new_env_24, 0, "/Users/adpusel/..", "", 24);

	chdir("/Users/adpusel");
	char *env_25[3] = { "OLDPATH=/toto", NULL };
	char *argv_25[3] = { "..", NULL };
	char *new_env_25[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_25, argv_25, new_env_25, 0, "/Users/adpusel/..", "", 25);

	chdir("/Users/adpusel");
	char *env_26[3] = { "OLDPATH=/toto", NULL };
	char *argv_26[3] = { "--", "..", NULL };
	char *new_env_26[2] = { "OLDPATH=/Users/adpusel", NULL };
	test_ms_cd(env_26, argv_26, new_env_26, 0, "/Users/adpusel/..", "", 26);


	// test change end file
	chdir("/Users/adpusel/code");
	char *env_27[3] = { "OLDPATH=/toto", NULL };
	char *argv_27[4] = { "--", "code", "toto", NULL };
	char *new_env_27[2] = { "OLDPATH=/Users/adpusel/code", NULL };
	test_ms_cd(env_27, argv_27, new_env_27, 0, "/Users/adpusel/toto", "", 27);

	// test change middle file
	chdir("/Users/adpusel/toto/t2/t1_1/t2_1");
	char *env_28[3] = { "OLDPATH=/toto", NULL };
	char *argv_28[3] = { "t2", "t1", NULL };
	char *new_env_28[2] = { "OLDPATH=/Users/adpusel/toto/t2/t1_1/t2_1", NULL };
	test_ms_cd(env_28, argv_28, new_env_28, 0, "/Users/adpusel/toto/t1/t1_1/t2_1", "", 28);

	// test change start file
	chdir("/private");
	char *env_29[3] = { "OLDPATH=/toto", NULL };
	char *argv_29[3] = { "/private", "/Users", NULL };
	char *new_env_29[2] = { "OLDPATH=/private", NULL };
	test_ms_cd(env_29, argv_29, new_env_29, 0, "/Users", "", 29);

	// with --
	chdir("/private");
	char *env_30[3] = { "OLDPATH=/toto", NULL };
	char *argv_30[4] = { "--", "/private", "/Users", NULL };
	char *new_env_30[2] = { "OLDPATH=/private", NULL };
	test_ms_cd(env_30, argv_30, new_env_30, 0, "/Users", "", 30);

	// Error, not in path
	chdir("/Users/adpusel/toto");
	char *env_31[3] = { "OLDPATH=/toto", NULL };
	char *argv_31[3] = { "/private", "tata", NULL };
	char *new_env_31[2] = { "OLDPATH=/toto", NULL };
	test_ms_cd(env_31, argv_31, new_env_31, -1, "", "cd: string not in pwd: /private\n", 31);

	// test no argv and no home
	chdir("/Users/adpusel/toto");
	char *env_32[3] = { "HOME=/Users/adpusel", NULL };
	char *argv_32[3] = { NULL };
	char *new_env_32[3] = { "HOME=/Users/adpusel", "OLDPATH=/Users/adpusel/toto", NULL };
	test_ms_cd(env_32, argv_32, new_env_32, 0, "/Users/adpusel", "", 32);

	// home do not exist || old path do not exist
	chdir("/Users/adpusel/toto");
	char *env_33[3] = { "HOME=/Users/adpus", NULL };
	char *argv_33[3] = { "./no_go" };
	char *new_env_33[3] = { "HOME=/Users/adpus", NULL };
	test_ms_cd(env_33, argv_33, new_env_33, -1, "/Users/adpusel/toto/./no_go",
			   "cd: permission denied: /Users/adpusel/toto/./no_go\n", 33);

	// file not exist
	chdir("/Users/adpusel/toto");
	char *env_34[3] = { "HOME=/Users/eaou", NULL };
	char *argv_34[3] = { NULL };
	char *new_env_34[3] = { "HOME=/Users/eaou", NULL };
	test_ms_cd(env_34, argv_34, new_env_34, -1, "/Users/eaou", "cd: no such file or directory: /Users/eaou\n", 34);

	int test = 0;
	test_get_all_command("toto et tata a la plag'e\n '", "toto et tata a la plag'e\n '", &test);
	test_get_all_command("''", "''", &test);
	test_get_all_command("'\"\"\"'''", "'\"\"\"'''", &test);
	test_get_all_command("\"\"", "\"\"", &test);
	test_get_all_command("toto et titi ' aoeuaou \n aoue \n aoeuaoeu '1  ' aoeuu \n aoeu \n '",
						 "toto et titi ' aoeuaou \n aoue \n aoeuaoeu '1  ' aoeuu \n aoeu \n '", &test);

	char space_0[20] = " toto ";
	test_transform_space(space_0, " toto ", 0);

	char space_1[20] = "' toto '";
	test_transform_space(space_1, " |toto| ", 1);

	char space_2[20] = "''";
	test_transform_space(space_2, "  ", 2);

	char space_3[200] = " 'd'  aaaa ' oeu'";
	test_transform_space(space_3, "  d   aaaa  |oeu ", 3);

	char space_4[200] = " ' super  te mo fi \" ' aaaa ' oeu'";
	test_transform_space(space_4, "  |super||te|mo|fi|\"|  aaaa  |oeu ", 4);

	char space_5[200] = "' aaaa ' uasdf";
	test_transform_space(space_5, " |aaaa|  uasdf", 5);

	char space_6[200] = "' aaaa ' uasdf";
	test_transform_space(space_6, " |aaaa|  uasdf", 6);
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

void test_all()
{
	t_ms *a = &ms;
	(void) a;

	tested_test();
//	test_read_command("toto", "toto", 1);
//	test_read_command("toto tata", "toto tata", 2);
//	test_read_command("\n", "", 3);
	test_read_command("toto    titi ' sam '", "toto;titi; sam ", 4);
	test_read_command("toto '   titi  '' sam '", "toto;   titi  ; sam ", 5);
	test_read_command("toto '   titi  '' sam \"' \" hy toto ss   '' '' '' ' \" ",
	                  "toto;   titi  ; sam \"; hy toto ss   '' '' '' ' ", 6);
}