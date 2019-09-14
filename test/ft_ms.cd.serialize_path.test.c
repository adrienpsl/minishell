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
# include "../src/cd/ft_ms.cd.serialize_path.c"

typedef struct s
{
	int nb_test;
	int nb_line;

	int size;
	char *env_str;
	char *argv_str;

	int result_int;
	char *result_str;
	char *result_print;
} t;

void test_init_g_ms(char *str)
{
	char **split = ft_strsplit(str, " ");

	ms__init(split);
	ft_strsplit_free(&split);
}
void static test_add_env_var(t t)
{
	g_test = 1;
	test_init_g_ms(t.env_str);

	int ret = add_env_var(g_ms.env, g_ms.buffer_cd, t.size);

	if (test_cmp_int(t.result_int, ret))
		log_test_line(t.nb_test, t.nb_line)
	if (test_cmp_str(t.result_str, g_ms.buffer_cd->data))
		log_test_line(t.nb_test, t.nb_line)
	if (test_cmp_testbuff(t.result_print))
		log_test_line(t.nb_test, t.nb_line);
	ms__free();
	g_test = 0;
}

void static test_replace_in_path(t t)
{
	g_test = 1;
	test_init_g_ms(t.env_str);
	char **argv = ft_strsplit(t.argv_str, " ");

	int ret = replace_in_path(argv, g_ms.buffer_cd);

	if (test_cmp_int(t.result_int, ret))
		log_test_line(t.nb_test, t.nb_line)
	if (test_cmp_str(t.result_str, g_ms.buffer_cd->data))
		log_test_line(t.nb_test, t.nb_line)
	if (test_cmp_testbuff(t.result_print))
		log_test_line(t.nb_test, t.nb_line)

	ft_strsplit_free(&argv);
	g_test = 0;
}

void static test_serialize_path(t t)
{
	g_test = 1;

	test_init_g_ms(t.env_str);
	char **argv = ft_strsplit(t.argv_str, " ");

	int ret = cd__serialize_path(argv, g_ms.env, g_ms.buffer_cd);

	if (test_cmp_int(t.result_int, ret))
		log_test_line(t.nb_test, t.nb_line)
	if (test_cmp_str(t.result_str, g_ms.buffer_cd->data))
		log_test_line(t.nb_test, t.nb_line)
	if (test_cmp_testbuff(t.result_print))
		log_test_line(t.nb_test, t.nb_line);

	ms__free();
	ft_strsplit_free(&argv);
	g_test = 0;
}

void test_cd__serialize_path()
{

	/*
	* test add_env_var
	* */
	{
		// error no Home
		test_add_env_var((t){ 0, L,
							  0, "PATH=Minh;jolie", "",
							  -1, "", MS__NAME"line 37: cd: HOME not set\n"
		});

		// error no oldpath
		test_add_env_var((t){ 0, L,
							  1, "PATH=Minh;jolie HOME=super", "",
							  -1, "", MS__NAME"line 37: cd: OLDPATH not set\n"
		});

		// test get home
		test_add_env_var((t){ 0, L,
							  0, "PATH=Minh;jolie HOME=super", "",
							  OK, "super", ""
		});

		// test get oldpath
		test_add_env_var((t){ 0, L,
							  1, "PATH=Minh;jolie HOME=super OLDPATH=mith", "",
							  OK, "mith", ""
		});
	}

	/*
	* test replace in path
	* */
	{
		// not in path
		test_replace_in_path((t){ 0, L, 1, "PATH=toto",
								  "aa oo",
								  -1,
								  "/Users/adpusel/code/42/minishell/cmake-build-debug",
								  "cd: string not in pwd: aa\n" });

		test_replace_in_path((t){ 0, L, 1, "PATH=toto",
								  "/Users titi",
								  OK,
								  "titi/adpusel/code/42/minishell/cmake-build-debug",
								  "" });
	}

	/*
	* test cd__serialize
	* */
	{
		// no argv
		test_serialize_path((t){ 0, L,
								 1, "PATH=Minh;jolie HOME=super OLDPATH=mith",
								 "",
								 OK, "super", ""
		});

		// no argv error
		test_serialize_path((t){ 0, L,
								 1, "PATH=Minh;jolie OLDPATH=mith",
								 "",
								 -1, "", "minishell: line 37: cd: HOME not set\n"
		});

		// no argv
		test_serialize_path((t){ 0, L,
								 1, "PATH=Minh;jolie HOME=super OLDPATH=mith",
								 "-",
								 OK, "mith", ""
		});

		// no argv error
		test_serialize_path((t){ 0, L,
								 1, "PATH=Minh;jolie",
								 "-",
								 -1, "", "minishell: line 37: cd: OLDPATH not set\n"
		});

		// one arg
		test_serialize_path((t){ 0, L,
								 1, "PATH=Minh;jolie",
								 "faire_des_chips",
								 OK, "faire_des_chips", ""
		});




		// -
		// 1
		// 2

	}
}