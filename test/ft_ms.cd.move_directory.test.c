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
# include "../src/cd/ft_ms.cd.move_to_directory.c"

void test_init_g_ms(char *str);

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


//void static test_serialize_path(t t)
//{
//	g_test = 1;
//
//	test_init_g_ms(t.env_str);
//	char **argv = ft_strsplit(t.argv_str, " ");
//
//	int ret = cd__serialize_path(argv, g_ms.env, g_ms.buffer_cd);
//
//	if (test_cmp_int(t.result_int, ret))
//		log_test_line(t.nb_test, t.nb_line)
//	if (test_cmp_str(t.result_str, g_ms.buffer_cd->data))
//		log_test_line(t.nb_test, t.nb_line)
//	if (test_cmp_testbuff(t.result_print))
//		log_test_line(t.nb_test, t.nb_line);
//
//	ms__free();
//	ft_strsplit_free(&argv);
//	g_test = 0;
//}


void test_cd_move_directory()
{
	/*
	* test add_start_if_relative
	* */
	{
		t_s *s = fts__init(10);

		// test with relative path
		fts__add(s, "toto");
		add_start_if_relative(s);
		if (test_cmp_str(
			"/Users/adpusel/code/42/minishell/cmake-build-debug/toto", s->data))
			log_test(1)

		// test with hard path
		fts__clear(s);
		fts__add(s, "/hey");
		if (test_cmp_str("/hey", s->data))
			log_test(2)

		fts__free(&s);
	}
	/*
	* test_and_go_dir
	* */
	{
		g_test = 1;
		// create 3 file
		// - one not dir
		// - one no access
		// - one no exist
		// - one good

		// test no- access
		{
			test_init_g_ms("PATH=taat");
			fts__add(g_ms.buffer_cd, "no_access");
			system("mkdir -p no_access");
			system("chmod 000 no_access");

			int ret = test_and_go_dir("no_access", "no_access");
			if (-1 != ret
				|| test_cmp_testbuff("cd: permission denied: no_access\n"))
				log_test(1)
		}

		// no exist
		{
			char *name = "no_exist";
			test_init_g_ms("PATH=taat");
			fts__add(g_ms.buffer_cd, name);
			int ret = test_and_go_dir(name, name);
			if (-1 != ret
				||
				test_cmp_testbuff("cd: no such file or directory: no_exist\n"))
				log_test(1)
		}

		// not a directory
		{
			system("touch is_file");
			char *name = "is_file";
			test_init_g_ms("PATH=taat");
			fts__add(g_ms.buffer_cd, name);
			int ret = test_and_go_dir(name, name);
			if (-1 != ret
				|| test_cmp_testbuff("cd: not a directory: is_file\n"))
				log_test(1)
		}

		// not a directory
		{
			system("mkdir -p good_dir");
			char *name = "good_dir";
			test_init_g_ms("PATH=taat");
			fts__add(g_ms.buffer_cd, name);
			int ret = test_and_go_dir(name, name);
			if (OK != ret
				|| test_cmp_testbuff(""))
				log_test(1)
			char *current = get_current_path();
			if (test_cmp_str(current,
							 "/Users/adpusel/code/42/minishell/cmake-build-debug/good_dir"))
				log_test(1)
			chdir("..");
		}

		g_test = 0;
	}
}
