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

void test_ms_env_copy(char **env, int ret, int error, int test)
{
	int intern_ret;
	ft_mem_set(&ms, 0, sizeof(ms));
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

void test_ms_env_add(char **env, char *new_var, int ret, char **res, int errno, int test)
{
	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env);
	int intern_ret;
	intern_ret = ms_env_add(new_var);
	if (((ms.env && !env) || (!ms.env && env))
		|| ft_str_split_cmp(ms.env, res)
		|| ret != intern_ret
		|| g_errno != errno)
	{
		printf("error test : %d \n", test);
	}
	g_errno = 0;
}

void test_ms_env_remove(char **env, char *deleting_key, int ret, char **res, int error, int test)
{
	int intern_ret;

	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env);
	intern_ret = ms_env_remove(deleting_key);
	if (ft_str_split_cmp(ms.env, res)
		|| ret != intern_ret
		|| error != g_errno)
	{
		printf("error test : %d \n", test);
	}
	g_errno = 0;
}

void test_ms_get_env_value(char **env, char *key, char *ret, int errno, int test)
{
	char *intern_ret;

	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env);
	intern_ret = env_get_value(key);
	if (ft_str_is_not(intern_ret, ret)
		|| g_errno != errno)
		printf("error test : %d \n", test);

	g_errno = 0;
}

void test_ms_env_modify(char **env, char *key, char *new_value, int ret, char **res, int error, int test)
{
	int intern_ret;

	ft_mem_set(&ms, 0, sizeof(ms));
	ms_env_copy(env);
	intern_ret = ms_env_modify(key, new_value);
	if (ft_str_split_cmp(ms.env, res)
		|| ret != intern_ret
		|| error != g_errno)
	{
		printf("error test : %d \n", test);
		ft_str_split_print(ms.env);
	}
	g_errno = 0;
}

void test_ms_cd(char **env, char **arg, int ret, int test, char *curpath, char **new_env, int error)
{
	int intern_ret;
	t_ms *a = &ms;
	(void) a;

	ft_mem_set(&ms, 0, sizeof(ms));
	ft_mem_zero(ms.testing_str, 10000);
	ms.test = 1;
	ms.buffer = ms.buffer_array;
	ms_env_copy(env);
	ms.arg = arg;
	intern_ret = ms_cd(arg);
	if (ret != intern_ret
		|| (curpath && ft_str_is_not(curpath, ms.testing_str))
		|| ft_str_split_cmp(new_env, ms.env)
		|| g_errno != error)
	{
		printf("test n : %d \n", test);
		printf("%s \n", ms.testing_str);
		printf("%d \n", g_errno);
	}
	g_errno = 0;
}

void test_all()
{
	t_ms *a = &ms;
	(void) a;
	//	//
	//	// test null
	//	test_ms_cd(NULL, NULL, -1, 18, NULL, 0);
	//
	//	// test -
	//	char *env_19[2] = { "OLDPATH=/Users/adpusel", NULL };
	//	char *new_env_19[2] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	//	char *argv_19[3] = { "-", NULL };
	//	test_ms_cd(env_19, argv_19, 0, 19, "/Users/adpusel", new_env_19, 0);
	//
	//	char *env_20[3] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	//	char *argv_20[3] = { "--", "-", NULL };
	//	char *new_env_20[2] = { "OLDPATH=/Users/adpusel", NULL };
	//	test_ms_cd(env_20, argv_20, 0, 20, "/Users/adpusel/code/42/minishell/cmake-build-debug", new_env_20, 0);
	//
	//	char *env_21[3] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	//	char *argv_21[3] = { "/Users/adpusel", NULL };
	//	char *new_env_21[2] = { "OLDPATH=/Users/adpusel/code/42/minishell/cmake-build-debug", NULL };
	//	test_ms_cd(env_21, argv_21, 0, 21, "/Users/adpusel", new_env_21, 0);

	//	chdir("/Users/adpusel");
	//	char *env_22[3] = { "OLDPATH=/toto", NULL };
	//	char *argv_22[3] = { "--", "/Users/adpusel/code", NULL };
	//	char *new_env_22[2] = { "OLDPATH=/Users/adpusel", NULL };
	//	test_ms_cd(env_22, argv_22, 0, 22, "/Users/adpusel/code", new_env_22, 0);

//	chdir("/Users/adpusel");
//	char *env_23[3] = { "OLDPATH=/toto", NULL };
//	char *argv_23[3] = { "--", "./code", NULL };
//	char *new_env_23[2] = { "OLDPATH=/Users/adpusel", NULL };
//	test_ms_cd(env_23, argv_23, 0, 23, "/Users/adpusel/./code", new_env_23, 0);
//
//	chdir("/Users/adpusel");
//	char *env_24[3] = { "OLDPATH=/toto", NULL };
//	char *argv_24[3] = { "..", NULL };
//	char *new_env_24[2] = { "OLDPATH=/Users/adpusel", NULL };
//	test_ms_cd(env_24, argv_24, 0, 24, "/Users/adpusel/..", new_env_24, 0);
//
//	chdir("/Users/adpusel");
//	char *env_25[3] = { "OLDPATH=/toto", NULL };
//	char *argv_25[3] = { "..", NULL };
//	char *new_env_25[2] = { "OLDPATH=/Users/adpusel", NULL };
//	test_ms_cd(env_25, argv_25, 0, 25, "/Users/adpusel/..", new_env_25, 0);
//
//
//	chdir("/Users/adpusel");
//	char *env_26[3] = { "OLDPATH=/toto", NULL };
//	char *argv_26[3] = { "--", "..", NULL };
//	char *new_env_26[2] = { "OLDPATH=/Users/adpusel", NULL };
//	test_ms_cd(env_26, argv_26, 0, 26, "/Users/adpusel/..", new_env_26, 0);
//
//
//	// test change end file
//	chdir("/Users/adpusel/code");
//	char *env_27[3] = { "OLDPATH=/toto", NULL };
//	char *argv_27[4] = { "--", "code", "toto", NULL };
//	char *new_env_27[2] = { "OLDPATH=/Users/adpusel/code", NULL };
//	test_ms_cd(env_27, argv_27, 0, 27, "/Users/adpusel/toto", new_env_27, 0);
//
//	// test change middle file
//	chdir("/Users/adpusel/toto/t2/t1_1/t2_1");
//	char *env_28[3] = { "OLDPATH=/toto", NULL };
//	char *argv_28[3] = { "t2", "t1", NULL };
//	char *new_env_28[2] = { "OLDPATH=/Users/adpusel/toto/t2/t1_1/t2_1", NULL };
//	test_ms_cd(env_28, argv_28, 0, 28, "/Users/adpusel/toto/t1/t1_1/t2_1", new_env_28, 0);

	// test change start file
	chdir("/private");
	char *env_29[3] = { "OLDPATH=/toto", NULL };
	char *argv_29[3] = { "/private", "/Users", NULL };
	char *new_env_29[2] = { "OLDPATH=/private", NULL };
	test_ms_cd(env_29, argv_29, 0, 29, "/Users", new_env_29, 0);

	//	//	 remplacement path :
	//	char *env_25[2] = { "OLDPATH=/Users/adpusel", NULL };
	//	char *argv_25[4] = { "--", "toto", "tata", NULL };
	//	test_ms_cd(env_25, argv_25, -1, 25, NULL, STR_NOT_IN_PATH);
	//
	//	// remplacement path :
	//	char *env_26[2] = { "OLDPATH=/Users/", NULL };
	//	char *argv_26[4] = { "--", "adpusel", "tata", NULL };
	//	test_ms_cd(env_26, argv_26, 0, 26, "/Users/tata/code/42/minishell/cmake-build-debug", 0);
	//
	//	char *env_27[2] = { "OLDPATH=/Users/", NULL };
	//	char *argv_27[4] = { "--", "/U", "tata", NULL };
	//	test_ms_cd(env_27, argv_27, 0, 27, "tatasers/adpusel/code/42/minishell/cmake-build-debug", 0);
	//
	//	char *env_28[2] = { "OLDPATH=/Users/", NULL };
	//	char *argv_28[4] = { "--", "cmake-build-debug", "toto", NULL };
	//	test_ms_cd(env_28, argv_28, 0, 28, "/Users/adpusel/code/42/minishell/toto", 0);
	//
	//	// test no argv // not home
	//	char *env_29[2] = { "toto=tata", NULL };
	//	char *argv_29[4] = { NULL };
	//	test_ms_cd(env_29, argv_29, -1, 29, NULL, HOME_HAS_BE_DELETED);
	//
	//	// no argv // home
	//	char *env_30[2] = { "HOME=tata", NULL };
	//	char *argv_30[4] = { NULL };
	//	test_ms_cd(env_30, argv_30, 0, 30, NULL, 0);


	//	char *test_1[1] = { NULL };
	//	test_ms_env_copy(test_1, 0, 0, 1);
	//
	//	char *test_2[4] = { "toto=super", "mimi=toto", "superTest", NULL };
	//	test_ms_env_copy(test_2, 0, 0, 2);
	//
	//	// test with var null && empty env
	//	char *env_3[2] = { NULL };
	//	test_ms_env_add(env_3, NULL, -1, NULL, BAD_VAR, 3);
	//
	//	// test var null && 1 var env
	//	char *env_4[2] = { "toto=tata" };
	//	test_ms_env_add(env_4, NULL, -1, NULL, BAD_VAR, 4);
	//
	//	// empty env
	//	char *env_5[2] = { NULL };
	//	char *res_5[2] = { "toto=tata" };
	//	test_ms_env_add(env_5, "toto=tata", 0, res_5, 0, 5);
	//
	//	// bad variable : no =
	//	char *env_6[2] = { NULL };
	//	char *res_6[2] = { NULL };
	//	test_ms_env_add(env_6, "tototata", -1, res_6, BAD_VAR, 6);
	//
	//	// bad variable : too much =
	//	char *env_7[2] = { "tata=toto" };
	//	char *res_7[2] = { "tata=toto" };
	//	test_ms_env_add(env_7, "toto=tata=", -1, res_7, BAD_VAR, 7);
	//
	//	char *env_8[2] = { "tata=toto" };
	//	char *res_8[2] = { "tata=toto", "super=titi" };
	//	test_ms_env_add(env_8, "super=titi", 0, res_8, 0, 8);
	//
	//	// no env
	//	char *env_88[2] = { NULL };
	//	char *res_88[2] = { NULL };
	//	test_ms_env_remove(env_88, "toto", -1, res_88, BAD_DELETING_KEY, 88);
	//
	//	// no key
	//	char *env_9[2] = { NULL };
	//	char *res_9[2] = { NULL };
	//	test_ms_env_remove(env_9, NULL, -1, res_9, BAD_DELETING_KEY, 9);
	//
	//	// no key and env
	//	char *env_10[2] = { "toto=titi" };
	//	test_ms_env_remove(env_10, NULL, -1, env_10, BAD_DELETING_KEY, 10);
	//
	//	// delete one
	//	char *env_11[2] = { "toto=tata" };
	//	char *res_11[2] = { NULL };
	//	test_ms_env_remove(env_11, "toto", 0, res_11, 0, 11);
	//
	//	// delete middle
	//	char *env_12[5] = { "suer=aaoeu", "toto=tata", "manger=chipes", "aaaaaaa", NULL };
	//	char *res_12[5] = { "suer=aaoeu", "manger=chipes", "aaaaaaa", NULL };
	//	test_ms_env_remove(env_12, "toto", 0, res_12, 0, 12);
	//
	//	// delete end
	//	char *env_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	char *res_13[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", NULL };
	//	test_ms_env_remove(env_13, "manger", 0, res_13, 0, 13);

	//	// no bad
	//	char *env_14[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	test_ms_get_env_value(env_14, "mange", NULL, 0, 14);
	//
	//	// null key
	//	char *env_15[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	test_ms_get_env_value(env_15, NULL, NULL, 0, 15);
	//
	//	// good key
	//		char *env_16[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//		test_ms_get_env_value(env_16, "suer", "aaoeu", 0, 16);
	//
	//	// good key
	//		char *env_17[5] = { "suer=aaoeu", "toto=", "aaaaaaa", "manger=chipes", NULL };
	//		test_ms_get_env_value(env_17, "toto", "", 0, 17);
	//

	// test ms_env_modify
	//	char *env_117[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=chipes", NULL };
	//	char *res_117[5] = { "suer=aaoeu", "toto=tata", "aaaaaaa", "manger=titi", NULL };
	//	test_ms_env_modify(env_117, "manger", "titi", 0, res_117, 0, 117);


}