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

# include <minishell.prototypes.h>
# include "../src/ft_ms.execve.c"

struct test
{
	int line_nb;

	char *env_str;
	char *argv_str;
	char *path_str;

	char *expect_print;
	char *expect_env;
	int expect_int;
};

void t_exec_binary(struct test t)
{
	g_test = 1;
	char **env = ft_strsplit(t.env_str, " ");
	char **argv = ft_strsplit(t.argv_str, " ");

	int ret = exec_binary(t.path_str, argv, env);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&env);
	ft_strsplit_free(&argv);
}

void t_find_and_check_binary(struct test t)
{
	g_test = 1;
	char **env = ft_strsplit(t.env_str, " ");
	char **argv = ft_strsplit(t.argv_str, " ");

	int ret = find_and_check_binary(argv, &env);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&env);
	ft_strsplit_free(&argv);
}

void t_loop_and_recursive(struct test t)
{
	g_test = 1;
	char **env = ft_strsplit(t.env_str, " ");
	char **argv = ft_strsplit(t.argv_str, " ");

	int ret = loop_and_recursive(argv, &env);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&env);
	ft_strsplit_free(&argv);
}

void t_ms__command(struct test t)
{
	g_test = 1;
	char **env = ft_strsplit(t.env_str, " ");

	int ret = ms__command(t.argv_str, &env);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&env);
}

void test__execve()
{
	// this is the file for the ls command
	system("mkdir -p test_dir");
	//	system("touch test_dir/file_1");

	/*
	* test exec_binary
	* */
	{
		// test good path
		t_exec_binary((struct test){ .line_nb = L,
			.path_str = "/bin/ls",
			.argv_str = "ls test_dir",
			.env_str = "",

			.expect_print = "",
			.expect_int = OK
		});
	}

	/*
	* test find_and_check binary
	* */
	{
		// good path
		t_find_and_check_binary((struct test){
			.line_nb = L,
			.argv_str = "/bin/ls test_dir",
			.env_str = "",

			.expect_print = "",
			.expect_int = OK
		});

		// bad path
		t_find_and_check_binary((struct test){
			.line_nb = L,
			.argv_str = "/in/ls test_dir",
			.env_str = "",

			.expect_print = "minishell: no such file or directory: /in/ls\n",
			.expect_int = -1
		});

		// good command
		t_find_and_check_binary((struct test){
			.line_nb = L,
			.argv_str = "ls test_dir",
			.env_str = "PATH=/bin",

			.expect_print = "",
			.expect_int = OK
		});

		// bad command
		t_find_and_check_binary((struct test){
			.line_nb = L,
			.argv_str = "lae test_dir",
			.env_str = "PATH=/bin",

			.expect_print = "minishell: command not found: lae\n",
			.expect_int = -1
		});
	}

	/*
	* test loop_and_recursive
	* */
	{
		// the env test
		{
			// simple env
			t_loop_and_recursive((struct test){
				.line_nb = L,
				.argv_str = "env",
				.env_str = "PATH=/bin",

				.expect_print = "PATH=/bin\n",
				.expect_int = OK
			});

			// env -i
			t_loop_and_recursive((struct test){
				.line_nb = L,
				.argv_str = "env -i toto=titi tata=toto",
				.env_str = "PATH=/bin",

				.expect_print = "toto=titi\ntata=toto\n",
				.expect_int = OK
			});

			// env -u
			t_loop_and_recursive((struct test){
				.line_nb = L,
				.argv_str = "env -u PATH",
				.env_str = "PATH=/bin",

				.expect_print = "\n",
				.expect_int = OK
			});

			// mixed of env
			t_loop_and_recursive((struct test){
				.line_nb = L,
				.argv_str = "env -i toto=titi env -u titi -u toto",
				.env_str = "PATH=/bin",

				.expect_print = "\n",
				.expect_int = OK
			});

			// mixed of env and after cd
			t_loop_and_recursive((struct test){
				.line_nb = L,
				.argv_str = "env -i toto=titi env -u titi -u toto env -i HOME=/ cd -",
				.env_str = "OLDPATH=/bin",

				.expect_print = "minishell: line 37: cd: OLDPATH not set\n",
				.expect_int = -1
			});

			// test if return 2 if exit
			// mixed of env and after cd
			t_loop_and_recursive((struct test){
				.line_nb = L,
				.argv_str = "exit",
				.env_str = "OLDPATH=/bin",

				.expect_print = "",
				.expect_int = 2
			});

			// test if return 2 if exit
			t_loop_and_recursive((struct test){
				.line_nb = L,
				.argv_str = "env -i toto=titi env -u titi -u toto env -i HOME=/ exit",
				.env_str = "OLDPATH=/bin",

				.expect_print = "",
				.expect_int = 2
			});
		}
	}

	/*
	* test of ms__command
	* */
	{
		// test empty line
		t_ms__command((struct test){
			.line_nb = L,
			.argv_str = "",
			.env_str = "OLDPATH=/bin",

			.expect_print = "",
			.expect_int = OK
		});


		// test with exit asked
		t_ms__command((struct test){
			.line_nb = L,
			.argv_str = "env -i toto=titi env -u titi -u toto env -i HOME=/ exit",
			.env_str = "OLDPATH=/bin",

			.expect_print = "",
			.expect_int = 2
		});

	}

	system("rm -rf test_dir");
}

