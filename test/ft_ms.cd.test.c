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

#include <libft.h>
#include "../src/ft_ms.cd.c"
#include "../src/ft_ms.cd.change_dir.c"
#include <ft_test.h>

struct test_cd
{
	int line_nb;

	char *path;
	char *argv;
	int print;
	int expect_int;
	char *env_str;

	char *expect_current_dir;
	char *expect_print;
	char *expect_env;
};

void func_test_change_directory(struct test_cd t)
{
	int ret = cd__change_directory(ft_strdup(t.path), t.argv, t.print);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_str(t.expect_current_dir, ftsystm__get_current_path())
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb);
	chdir("/Users/adpusel/code/42/minishell_new/cmake-build-debug");
}

void f_one_and_zero_argv(struct test_cd t)
{
	char **env = ft_strsplit(t.env_str, " ");
	int ret = one_and_zero_argv(t.argv, env);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_str(t.expect_current_dir, ftsystm__get_current_path())
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb);

	chdir("/Users/adpusel/code/42/minishell_new/cmake-build-debug");
	ft_strsplit_free(&env);
}

void test_two_argument(struct test_cd t)
{
	char *current_dir = ftsystm__get_current_path();
	char **argv = ft_strsplit(t.argv, " ");

	int ret = two_argument(argv, current_dir);
	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_str(t.expect_current_dir, ftsystm__get_current_path())
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb);

	ft_strsplit_free(&argv);
	chdir("/Users/adpusel/code/42/minishell_new/cmake-build-debug");
}

void test_ms_cd(struct test_cd t)
{
	char **argv = ft_strsplit(t.argv, " ");
	char **env = ft_strsplit(t.env_str, "");

	int ret = ms__cd(argv, &env);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_str(t.expect_current_dir, ftsystm__get_current_path())
		|| test_cmp_buff(t.expect_print ? t.expect_print : ""))
		log_test_line(1, t.line_nb)

	ft_strsplit_print(env, ' ');
	if (test_cmp_buff(t.expect_env))
		log_test_line(1, t.line_nb)

	ft_strsplit_free(&argv);
	chdir("/Users/adpusel/code/42/minishell_new/cmake-build-debug");
}

void test__main_cd()
{
	g_test = 1;
	char *start_directory = "/Users/adpusel/code/42/minishell_new/cmake-build-debug";
	/*
	* test change directory
	* */
	{
		// test if null
		func_test_change_directory((struct test_cd){ .line_nb = L,
			.path= NULL, .argv= "toto", .print= 1,
			.expect_int = -1,
			.expect_current_dir = start_directory,
			.expect_print = "" }
		);

		// test if relative
		func_test_change_directory((struct test_cd){ .line_nb = L,
			.path="../", .argv= "toto", .print= 0,
			.expect_int = OK,
			.expect_current_dir = "/Users/adpusel/code/42/minishell_new",
			.expect_print = "" }
		);

		// test if hard
		func_test_change_directory((struct test_cd){ .line_nb = L,
			.path="/Users/adpusel/code/42/minishell_new", .argv= "toto", .print= 0,
			.expect_int = OK,
			.expect_current_dir = "/Users/adpusel/code/42/minishell_new",
			.expect_print = "" }
		);

		// if print
		func_test_change_directory((struct test_cd){ .line_nb = L,
			.path="/Users/adpusel/code/42/minishell_new", .argv= "toto", .print= 1,
			.expect_int = OK,
			.expect_current_dir = "/Users/adpusel/code/42/minishell_new",
			.expect_print = "/Users/adpusel/code/42/minishell_new\n" }
		);

		// if error and print
		func_test_change_directory((struct test_cd){ .line_nb = L,
			.path="/Users/adpusel/code/4asoeuohew", .argv= "test_error", .print= 1,
			.expect_int = -1,
			.expect_current_dir = start_directory,
			.expect_print = "cd: no such file or directory: test_error\n" }
		);
	}

	/*
	* test one_and_zero_argv
	* */
	{
		// test with oldpath
		f_one_and_zero_argv((struct test_cd){ .line_nb = L,
			.argv= "-", .env_str="OLDPATH=/",
			.expect_int = OK,
			.expect_current_dir = "/",
			.expect_print = "/\n" }
		);

		// test with oldpath bad
		f_one_and_zero_argv((struct test_cd){ .line_nb = L,
			.argv= "-", .env_str="OLDPATH=/aeu",
			.expect_int = -1,
			.expect_current_dir = start_directory,
			.expect_print = "cd: no such file or directory: /aeu\n" }
		);

		// not have oldpath
		f_one_and_zero_argv((struct test_cd){ .line_nb = L,
			.argv= "-", .env_str="OLDPAH=/aeu",
			.expect_int = -1,
			.expect_current_dir = start_directory,
			.expect_print = "minishell: line 36: cd: OLDPATH not set\n" }
		);

		// with home
		f_one_and_zero_argv((struct test_cd){ .line_nb = L,
			.argv= NULL, .env_str="HOME=/",
			.expect_int = OK,
			.expect_current_dir = "/",
			.expect_print = "" }
		);

		// not have home
		f_one_and_zero_argv((struct test_cd){ .line_nb = L,
			.argv= NULL, .env_str="HOM=/aeu",
			.expect_int = -1,
			.expect_current_dir = start_directory,
			.expect_print = "minishell: line 36: cd: HOME not set\n" }
		);

		// with classic argument
		f_one_and_zero_argv((struct test_cd){ .line_nb = L,
			.argv= "/", .env_str="HOM=/aeu",
			.expect_int = OK,
			.expect_current_dir = "/",
			.expect_print = "" }
		);
	}

	/*
	* test two_argument
	* */
	{
		// test good change and good path
		test_two_argument((struct test_cd){ .line_nb = L,
			.argv= "minishell_new libft",
			.expect_int = OK,
			.expect_current_dir = "/Users/adpusel/code/42/libft/cmake-build-debug",
			.expect_print = "/Users/adpusel/code/42/libft/cmake-build-debug\n" }
		);

		// test good change and bad path
		test_two_argument((struct test_cd){ .line_nb = L,
			.argv= "minishell_new bite",
			.expect_int = -1,
			.expect_current_dir = start_directory,
			.expect_print = "cd: no such file or directory: /Users/adpusel/code/42/bite/cmake-build-debug\n" }
		);

		// test bad change good path
		test_two_argument((struct test_cd){ .line_nb = L,
			.argv= "aoeu bite",
			.expect_int = -1,
			.expect_current_dir = start_directory,
			.expect_print = "cd: string not in pwd: aoeu\n" }
		);
	}

	/*
	* test
	* */
	{
		/*
		* function specific
		* */
		{
			// test no avancte with --
			test_ms_cd((struct test_cd){ .line_nb = L,
					.argv= "-- -", .env_str = "OLDPATH=/",

					.expect_int = OK,
					.expect_current_dir = "/",
					.expect_print = "/\n",
					.expect_env = "OLDPATH=/Users/adpusel/code/42/minishell_new/cmake-build-debug"
				}
			);

			// test too much argv
			test_ms_cd((struct test_cd){ .line_nb = L,
					.argv= "1 2 3", .env_str = "OLDPAT=/",

					.expect_int = -1,
					.expect_current_dir = start_directory,
					.expect_print = "cd: to much argument\n",
					.expect_env = "OLDPAT=/"
				}
			);
		}

		// test with good path
		test_ms_cd((struct test_cd){ .line_nb = L,
				.argv= "", .env_str = "HOME=/",

				.expect_int = OK,
				.expect_current_dir = "/",
				.expect_print = "",
				.expect_env = "HOME=/ OLDPATH=/Users/adpusel/code/42/minishell_new/cmake-build-debug"
			}
		);

		//		// test bad home
		//		test_ms_cd((struct test_cd){ .line_nb = L,
		//				.argv= "", .env_str = "HOME=aoeu",
		//
		//				.expect_int = -1,
		//				.expect_current_dir = start_directory,
		//				.expect_print = "cd: no such file or directory: aoeu\n",
		//				.expect_env = "HOME=aoeu"
		//			}
		//		);
		//
		//		// test bad home
		//		test_ms_cd((struct test_cd){ .line_nb = L,
		//				.argv= "", .env_str = "HOME=aoeu",
		//
		//				.expect_int = -1,
		//				.expect_current_dir = start_directory,
		//				.expect_print = "cd: no such file or directory: aoeu\n",
		//				.expect_env = "HOME=aoeu"
		//			}
		//		);


		// test oldpath
		test_ms_cd((struct test_cd){ .line_nb = L,
				.argv= "-", .env_str = "OLDPATH=/",

				.expect_int = OK,
				.expect_current_dir = "/",
				.expect_print = "/\n",
				.expect_env = "OLDPATH=/Users/adpusel/code/42/minishell_new/cmake-build-debug"
			}
		);

		// test no oldpath
		test_ms_cd((struct test_cd){ .line_nb = L,
				.argv= "-", .env_str = "OLDPAT=/",

				.expect_int = -1,
				.expect_current_dir = start_directory,
				.expect_print = "minishell: line 36: cd: OLDPATH not set\n",
				.expect_env = "OLDPAT=/"
			}
		);

		/*
		* 2 arguments
		* */
		{
			// test with 2 arguments bad no found
			test_ms_cd((struct test_cd){ .line_nb = L,
					.argv= "aoeu a", .env_str = "OLDPAT=/",

					.expect_int = -1,
					.expect_current_dir = start_directory,
					.expect_print = "cd: string not in pwd: aoeu\n",
					.expect_env = "OLDPAT=/"
				}
			);

			// 2 arguments bad path
			test_ms_cd((struct test_cd){ .line_nb = L,
					.argv= "mini tata", .env_str = "OLDPAT=/",

					.expect_int = -1,
					.expect_current_dir = start_directory,
					.expect_print = "cd: no such file or directory: /Users/adpusel/code/42/tatashell_new/cmake-build-debug\n",
					.expect_env = "OLDPAT=/"
				}
			);

			// 2 arguments good
			// test oldpath
			test_ms_cd((struct test_cd){ .line_nb = L,
					.argv= "minishell_new libft", .env_str = "OLDPATH=/",

					.expect_int = OK,
					.expect_current_dir = "/Users/adpusel/code/42/libft/cmake-build-debug",
					.expect_print = "/Users/adpusel/code/42/libft/cmake-build-debug\n",
					.expect_env = "OLDPATH=/Users/adpusel/code/42/minishell_new/cmake-build-debug"
				}
			);
		}
	}
}