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
	char *result_buffer;
	char *result_path;
	char *result_oldpath;
	char *result_print;
} t;

void static test_move_directory(t t)
{
	g_test = 1;
	// set up
	test_init_g_ms(t.env_str);
	system("mkdir -p move_test_dir");
	fts__add(g_ms.buffer_cd, t.argv_str);

	// call
	int ret = cd_move_directory(g_ms.buffer_cd, g_ms.env);

	// test
	if (test_cmp_int(t.result_int, ret)
		|| test_cmp_str(t.result_buffer, g_ms.buffer_cd->data))
		log_test(1)

	char *current = get_current_path();
	if (test_cmp_str(t.result_path, current))
		log_test(1)

	char *oldpath = ms__find_env_key(g_ms.env, "OLDPATH");
	if (test_cmp_str(t.result_oldpath, oldpath))
		log_test(1)

	if (t.result_print
		&& test_cmp_buff(t.result_print))
		log_test(1)

	// clean
	chdir("..");
	ms__free();
	g_test = 0;
}

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

		// test no- access
		{
			test_init_g_ms("PATH=taat");
			fts__add(g_ms.buffer_cd, "no_access");
			system("mkdir -p no_access");
			system("chmod 000 no_access");

			int ret = test_and_go_dir("no_access", "no_access");
			if (-1 != ret
				|| test_cmp_buff("cd: permission denied: no_access\n"))
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
				test_cmp_buff("cd: no such file or directory: no_exist\n"))
				log_test(1)
			ms__free();
		}

		// not a directory
		{
			system("touch is_file");
			char *name = "is_file";
			test_init_g_ms("PATH=taat");
			fts__add(g_ms.buffer_cd, name);

			int ret = test_and_go_dir(name, name);

			if (-1 != ret
				|| test_cmp_buff("cd: not a directory: is_file\n"))
				log_test(1)

			ms__free();
		}

		// not a directory
		{
			system("mkdir -p good_dir");
			char *name = "good_dir";
			test_init_g_ms("PATH=taat");
			fts__add(g_ms.buffer_cd, name);

			int ret = test_and_go_dir(name, name);

			if (OK != ret
				|| test_cmp_buff(""))
				log_test(1)

			char *current = get_current_path();
			if (test_cmp_str(current,
							 "/Users/adpusel/code/42/minishell/cmake-build-debug/good_dir"))
				log_test(1)

			chdir("..");
			ms__free();
		}

		g_test = 0;
	}

	/*
	* test move director
	* */
	{
		// test relative path
		{
			test_move_directory((t){
				.argv_str = "move_test_dir",
				.env_str = "PATH=toto",

				.result_int = OK,
				.result_path = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
				.result_buffer = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
				.result_oldpath = "/Users/adpusel/code/42/minishell/cmake-build-debug"
			});
		}

		// test absolute path
		{
			test_move_directory((t){
				.argv_str = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
				.env_str = "PATH=toto OLDPATH=super",

				.result_int = OK,
				.result_path = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
				.result_buffer = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
				.result_oldpath = "/Users/adpusel/code/42/minishell/cmake-build-debug"
			});
		}

		// test change bien OLDPATH
		test_move_directory((t){
			.argv_str = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
			.env_str = "PATH=toto OLDPATH=super",

			.result_int = OK,
			.result_buffer = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
			.result_oldpath = "/Users/adpusel/code/42/minishell/cmake-build-debug",
			.result_path = "/Users/adpusel/code/42/minishell/cmake-build-debug/move_test_dir",
			.result_print = ""
		});

		// Test error
		test_move_directory((t){
			.argv_str = "prout",
			.env_str = "PATH=toto OLDPATH=super",

			.result_int = -1,
			.result_buffer = "/Users/adpusel/code/42/minishell/cmake-build-debug/prout",
			.result_oldpath = "super",
			.result_path = "/Users/adpusel/code/42/minishell/cmake-build-debug",
			.result_print = "cd: no such file or directory: prout\n"
		});
	}
}
