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
	char *expect_char;
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

	int ret = find_and_launch_binary(argv, &env);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&env);
	ft_strsplit_free(&argv);
}

void t_loop_and_recursive(struct test t)
{
	g_test = 1;

	t_env e;
	t_data d;
	ft_bzero(&e, sizeof(t_env));
	ft_bzero(&d, sizeof(t_data));
	e.env = ft_strsplit(t.env_str, " ");
	d.argv = ft_strsplit(t.argv_str, " ");

	int ret = dispatch_between_binary_and_builtin(&d, &e);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&e.env);
	ft_strsplit_free(&d.argv);
}

void t_ms__command(struct test t)
{
	g_test = 1;
	t_env e;
	ft_bzero(&e, sizeof(t_env));
	e.env = ft_strsplit(t.env_str, " ");
	int ret = ms__command(t.argv_str, &e);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	free_env(&e);
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
* test loop on event
* */
	{
		// no arguments
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env",
			.env_str = "toto=titi",

			.expect_int = OK,
			.expect_print= "toto=titi\n",
			.expect_char = "toto=titi"
		});

		// -i no arguments
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -i tata",
			.env_str = "toto=titi",
			.expect_int = -1,
			.expect_print= "minishell: command not found: tata\n",
			.expect_char = ""
		});

		// -i good arguments
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -i tata=ou",
			.env_str = "toto=titi",

			.expect_print= "tata=ou\n",
			.expect_char = NULL
		});

		// -i good arguments and programme
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -i tata=ou hey",
			.env_str = "toto=titi",

			.expect_int = -1,
			.expect_print= "minishell: command not found: hey\n",
			.expect_char ="tata=ou"
		});

		// -u bad
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -u",
			.env_str = "toto=titi",

			.expect_int = -1,
			.expect_print= "env: option requires an argument -- u\n""usage: env [-i] [name=value ...] [-u name]\n""          [utility [argument ...]]\n",
			.expect_char = NULL
		});

		// -u good no arguments
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -u toto",
			.env_str = "toto=titi a=1 b=2",

			.expect_print= "a=1\nb=2\n",
			.expect_char = NULL
		});

		// -u good argument
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -u toto aa",
			.env_str = "toto=titi a=1 b=2",

			.expect_int = -1,
			.expect_print= "minishell: command not found: aa\n",
			.expect_char ="a=1 b=2"
		});

		// muliple env stuff
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -u toto env -u a a",
			.env_str = "toto=titi a=1 b=2",

			.expect_int = -1,
			.expect_print= "minishell: command not found: a\n",
			.expect_char ="b=2"
		});

		// other multiple
		t_ms__command((struct test){ .line_nb = L,
			.argv_str = "env -u toto env -u a env -i aa=bb",
			.env_str = "toto=titi a=1 b=2",

			.expect_print= "aa=bb\n",
			.expect_char = NULL
		});
	}


	/*
	* test loop_and_recursive
	* */
	{
		// the env test
		{
			// simple env
			//			t_loop_and_recursive((struct test){
			//				.line_nb = L,
			//				.argv_str = "env",
			//				.env_str = "PATH=/bin",
			//
			//				.expect_print = "PATH=/bin\n",
			//				.expect_int = OK
			//			});

			//			// env -i
			//			t_loop_and_recursive((struct test){
			//				.line_nb = L,
			//				.argv_str = "env -i toto=titi tata=toto",
			//				.env_str = "PATH=/bin",
			//
			//				.expect_print = "toto=titi\ntata=toto\n",
			//				.expect_int = OK
			//			});
			//
			//			// env -u
			//			t_loop_and_recursive((struct test){
			//				.line_nb = L,
			//				.argv_str = "env -u PATH",
			//				.env_str = "PATH=/bin",
			//
			//				.expect_print = "\n",
			//				.expect_int = OK
			//			});
			//
			//			// mixed of env
			//			t_loop_and_recursive((struct test){
			//				.line_nb = L,
			//				.argv_str = "env -i toto=titi env -u titi -u toto",
			//				.env_str = "PATH=/bin",
			//
			//				.expect_print = "\n",
			//				.expect_int = OK
			//			});
			//
			//			// mixed of env and after cd
			//			t_loop_and_recursive((struct test){
			//				.line_nb = L,
			//				.argv_str = "env -i toto=titi env -u titi -u toto env -i HOME=/ cd -",
			//				.env_str = "OLDPATH=/bin",
			//
			//				.expect_print = "minishell: line 39: cd: OLDPATH not set\n",
			//				.expect_int = -1
			//			});
			//
			//			// test if return 2 if exit
			//			// mixed of env and after cd
			//			t_loop_and_recursive((struct test){
			//				.line_nb = L,
			//				.argv_str = "exit",
			//				.env_str = "OLDPATH=/bin",
			//
			//				.expect_print = "",
			//				.expect_int = 2
			//			});
			//
			//			// test if return 2 if exit
			//			t_loop_and_recursive((struct test){
			//				.line_nb = L,
			//				.argv_str = "env -i toto=titi env -u titi -u toto env -i HOME=/ exit",
			//				.env_str = "OLDPATH=/bin",
			//
			//				.expect_print = "",
			//				.expect_int =  MS__EXIT
			//			});
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

			.expect_print = "minishell: command not found: exit\n",
			.expect_int = -1
		});
	}

	system("rm -rf test_dir");
}

