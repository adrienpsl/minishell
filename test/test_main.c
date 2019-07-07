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

#include "minishell.h"
int g_ft_errno;

void test_ms_env_copy(char **env, int ret, int test)
{
	t_ms ms;
	int intern_ret;
	ft_mem_set(&ms, 0, sizeof(ms));
	intern_ret = ms_env_copy(env, &ms);
	if (((ms.p_env && !env) || (!ms.p_env && env))
		|| ft_str_split_cmp(ms.p_env, env)
		|| ret != intern_ret)
	{
		printf("error test : %d \n", test);
	}
	//	ft_str_split_print(ms.p_env);
}

void test_ms_env_add(char **env, char *new_var, int ret, char **res, int test)
{
	t_ms ms;
	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env, &ms);
	int intern_ret;
	intern_ret = ms_env_add(new_var, &ms);
	if (((ms.p_env && !env) || (!ms.p_env && env))
		|| ft_str_split_cmp(ms.p_env, res)
		|| ret != intern_ret)
	{
		printf("error test : %d \n", test);
	}
}

void test_ms_env_remove(char **env, char *deleting_key, int ret, char **res, int test)
{
	t_ms ms;
	int intern_ret;

	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env, &ms);
	intern_ret = ms_env_remove(deleting_key, &ms);
	if (ft_str_split_cmp(ms.p_env, res)
		|| ret != intern_ret)
	{
		printf("error test : %d \n", test);
	}
}

void test_ms_get_env_value(char **env, char *key, char *ret, int test)
{
	t_ms ms;
	char *intern_ret;

	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env, &ms);
	intern_ret = ms_get_env_value(key, ms.p_env);
	if (ft_str_eq(intern_ret, ret))
		printf("error test : %d \n", test);
}

void test_ms_cd(char **env, char **arg, char ret, int test, char *curpath, int error)
{
	t_ms ms;
	int intern_ret;

	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env, &ms);
	ms.arg = arg;
	intern_ret = ms_cd(&ms);
	if (ret != intern_ret || (curpath && ft_str_eq(curpath, ms.curpath)) || g_ft_errno != error)
	{
		printf("%d \n", test);
		printf("%s \n",ms.curpath);
	}
	g_ft_errno = 0;
}

void test_all()
{

	// test null
	test_ms_cd(NULL, NULL, 0, 18, NULL, 0);

	// test -
	char *env_19[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_19[3] = { "-", NULL };
	test_ms_cd(env_19, argv_19, 0, 19, "/Users/adpusel", 0);

	// test -- -
	char *env_20[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_20[3] = { "--", "-", NULL };
	test_ms_cd(env_20, argv_20, 0, 20, "/Users/adpusel", 0);

	// simple path
	char *env_21[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_21[3] = { "/Users/adpusel", NULL };
	test_ms_cd(env_21, argv_21, 0, 21, "/Users/adpusel", 0);

	char *env_211[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_211[3] = { "--", "/Users/adpusel", NULL };
	test_ms_cd(env_211, argv_211, 0, 211, "/Users/adpusel", 0);

	// relative path
	char *env_22[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_22[3] = { "./Users/adpusel", NULL };
	test_ms_cd(env_22, argv_22, 0, 22, "/Users/adpusel/code/42/minishell/cmake-build-debug/./Users/adpusel", 0);

	// relative path 2
	char *env_23[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_23[3] = { "..", NULL };
	test_ms_cd(env_23, argv_23, 0, 23, "/Users/adpusel/code/42/minishell/cmake-build-debug/..", 0);

	// relative path 3
	char *env_24[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_24[3] = { "--", "..", NULL };
	test_ms_cd(env_24, argv_24, 0, 24, "/Users/adpusel/code/42/minishell/cmake-build-debug/..", 0);

	//	 remplacement path :
	char *env_25[2] = { "OLDPATH=/Users/adpusel", NULL };
	char *argv_25[4] = { "--", "toto", "tata", NULL };
	test_ms_cd(env_25, argv_25, -1, 25, NULL, STR_NOT_IN_PATH);

	// remplacement path :
	char *env_26[2] = { "OLDPATH=/Users/", NULL };
	char *argv_26[4] = { "--", "adpusel", "tata", NULL };
	test_ms_cd(env_26, argv_26, 0, 26, "/Users/tata/code/42/minishell/cmake-build-debug", 0);

	char *env_27[2] = { "OLDPATH=/Users/", NULL };
	char *argv_27[4] = { "--", "/U", "tata", NULL };
	test_ms_cd(env_27, argv_27, 0, 27, "tatasers/adpusel/code/42/minishell/cmake-build-debug", 0);

	char *env_28[2] = { "OLDPATH=/Users/", NULL };
	char *argv_28[4] = { "--", "cmake-build-debug", "toto", NULL };
	test_ms_cd(env_28, argv_28, 0, 28, "/Users/adpusel/code/42/minishell/toto", 0);



	//	test_ms_env_copy(NULL, NO_ENV, 0);
	//
	//	char *test_1[1] = { NULL };
	//	test_ms_env_copy(test_1, 0, 1);
	//
	//	char *test_2[4] = { "toto=super", "mimi=toto", "superTest", NULL };
	//	test_ms_env_copy(test_2, 0, 2);
	//
	//	// test with var null && empty env
	//	char *env_3[2] = { NULL };
	//	test_ms_env_add(env_3, NULL, BAD_VAR, NULL, 3);
	//
	//	// test var null && 1 var env
	//	char *env_4[2] = { "toto=tata" };
	//	test_ms_env_add(env_4, NULL, BAD_VAR, NULL, 4);
	//
	//	// empty env
	//	char *env_5[2] = { NULL };
	//	char *res_5[2] = { "toto=tata" };
	//	test_ms_env_add(env_5, "toto=tata", 0, res_5, 5);
	//
	//	// bad variable : no =
	//	char *env_6[2] = { NULL };
	//	char *res_6[2] = { NULL };
	//	test_ms_env_add(env_6, "tototata", BAD_VAR, res_6, 6);
	//
	//	// bad variable : too much =
	//	char *env_7[2] = { "tata=toto" };
	//	char *res_7[2] = { "tata=toto" };
	//	test_ms_env_add(env_7, "toto=tata=", BAD_VAR, res_7, 7);
	//
	//	// all good
	//	char *env_8[2] = { "tata=toto" };
	//	char *res_8[2] = { "tata=toto", "super=titi" };
	//	test_ms_env_add(env_8, "super=titi", 0, res_8, 8);
	//
	//	// no env
	//	char *env_88[2] = { NULL };
	//	char *res_88[2] = { NULL };
	//	test_ms_env_remove(env_88, "toto", BAD_DELETING_KEY, res_88, 88);
	//
	//	// no key
	//	char *env_9[2] = { NULL };
	//	char *res_9[2] = { NULL };
	//	test_ms_env_remove(env_9, NULL, BAD_DELETING_KEY, res_9, 9);
	//
	//	// no key and env
	//	char *env_10[2] = { "toto=titi" };
	//	test_ms_env_remove(env_10, NULL, BAD_DELETING_KEY, env_10, 10);
	//
	//	// delete one
	//	char *env_11[2] = { "toto=tata" };
	//	char *res_11[2] = { NULL };
	//	test_ms_env_remove(env_11, "toto", 0, res_11, 11);
	//
	//	// delete middle
	//	char *env_12[5] = { "suer=aaoeu", "toto=tata", "manger=chipes", "aaaaaaa", NULL };
	//	char *res_12[5] = { "suer=aaoeu", "manger=chipes", "aaaaaaa", NULL };
	//	test_ms_env_remove(env_12, "toto", 0, res_12, 12);
	//
	//	// delete end
	//	char *env_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	char *res_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", NULL };
	//	test_ms_env_remove(env_13, "manger", 0, res_13, 13);
	//
	//	// no bad
	//	char *env_14[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	test_ms_get_env_value(env_14, "mange", NULL, 14);
	//
	//	// null key
	//	char *env_15[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	test_ms_get_env_value(env_15, NULL, NULL, 15);
	//
	//	// good key
	//	char *env_16[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	test_ms_get_env_value(env_16, "suer", "aaoeu", 16);
	//
	//	// good key
	//	char *env_17[5] = { "suer=aaoeu", "toto=", "aaaaaaa", "manger=chipes", NULL };
	//	test_ms_get_env_value(env_17, "toto", "", 17);
}