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
#include "../src/env/ft_ms.env.c"

typedef struct s
{
	int nb_test;
	int nb_line;
	//
	char *argv_string;
	char *env_string;
	//
	int result_int;
	char *result_env_string;
	char *result_argv_string;
	char *result_error_string;
} t;

int test_cmp_split_str(char *name, char *expected, char **returned)
{
	g_test = 1;
	test_clear_testbuff();
	ft_strsplit_print(returned, ' ');

	if (test_cmp_testbuff(expected))
	{
		printf("%s", name);
		return (1);
	}
	g_test = 0;
	return (0);
}

int test_cmp_env_str(char *name, char *expected, t_array *env)
{
	g_test = 1;
	test_clear_testbuff();
	ftarray__func(env, ms__print_env, (void *)1);

	if (test_cmp_testbuff(expected))
	{
		printf("\n%s\n", name);
		return (1);
	}
	g_test = 0;
	return (0);
}

int test_cmp_int(int expected, int returned)
{
	if (expected != returned)
	{
		printf("error return : \n");
		printf("expected : %d \n", expected);
		printf("returned : %d \n", returned);
		return (1);
	}
	return (0);
}

void test_env_option_i(t t)
{
	// function data
	char **argv_start = ft_strsplit(t.argv_string, " ");
	char **argv = argv_start;

	// return function
	int function_return;
	t_array *env_tmp = NULL;

	// function call
	function_return = option_i(&argv, &env_tmp);

	if (
		test_cmp_int(t.result_int, function_return)
		|| // function argv forward test
		test_cmp_split_str("argv forward", t.result_argv_string, argv)
		||// function test env
		test_cmp_env_str("env test", t.result_env_string, env_tmp)
		)
		log_test_line(t.nb_test, t.nb_line)


	// free function data
	ft_strsplit_free(&argv_start);

	// free function created data
	if (env_tmp)
		ftarray__free_func(&env_tmp, ms__func_free_env, NULL);
}

void test_env_option_u(t t)
{
	// function data
	char **argv_start = ft_strsplit(t.argv_string, " ");
	char **argv = argv_start;

	char **split_tmp = ft_strsplit(t.env_string, " ");
	t_array *sys_env = ms__parse_env(split_tmp);
	ft_strsplit_free(&split_tmp);

	// return function
	int function_return;
	t_array *env_tmp = NULL;

	// function call
	function_return = option_u(&argv, sys_env, &env_tmp);

	// function result test
	if (
		test_cmp_int(t.result_int, function_return)
		|| // function argv forward test
		test_cmp_split_str("argv forward", t.result_argv_string, argv)
		||// function test env
		test_cmp_env_str("env test", t.result_env_string, env_tmp)
		)
		log_test_line(t.nb_test, t.nb_line)

	// free function data
	ft_strsplit_free(&argv_start);
	ftarray__free_func(&sys_env, ms__func_free_env, NULL);

	// free function created data
	if (env_tmp)
		ftarray__free_func(&env_tmp, ms__func_free_env, NULL);
}

void test_handle_option(t t)
{
	// function data
	char **argv_start = ft_strsplit(t.argv_string, " ");
	char **argv = argv_start;

	char **split_tmp = ft_strsplit(t.env_string, " ");
	t_array *sys_env = ms__parse_env(split_tmp);
	ft_strsplit_free(&split_tmp);

	// return function
	int function_return;
	t_array *env_tmp = NULL;

	// function call
	function_return = handle_options(&argv, sys_env, &env_tmp);

	// function result test
	if (
		test_cmp_int(t.result_int, function_return)
		|| test_cmp_testbuff(t.result_error_string)
		)
		log_test_line(t.nb_test, t.nb_line)

	// free function data
	ft_strsplit_free(&argv_start);
	ftarray__free_func(&sys_env, ms__func_free_env, NULL);

	// free function created data
	if (env_tmp)
		ftarray__free_func(&env_tmp, ms__func_free_env, NULL);
}

void test_ms__env()
{
	/*
	* test env_option_i
	* */
	if (1)
	{
		// test with no param
		{
			test_env_option_i((t){
				.nb_test = 0,
				.nb_line = L,
				.argv_string = "",
				.result_int = OK,
				.result_env_string = "",
				.result_argv_string = ""
			});
		}

		// test with one good param
		{
			test_env_option_i((t){
				.nb_test = 1,
				.nb_line = L,
				.argv_string = "hey=salut",
				.result_int = OK,
				.result_env_string = "hey=salut ",
				.result_argv_string = ""
			});
		}

		// test with two good param
		{
			test_env_option_i((t){
				.nb_test = 2,
				.nb_line = L,
				.argv_string = "hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "hey=salut comment=cava? ",
				.result_argv_string = ""
			});
		}

		// test with 2x2 same argv
		{
			test_env_option_i((t){
				.nb_test = 3,
				.nb_line = L,
				.argv_string = "hey=salut comment=cava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "hey=salut comment=cava? ",
				.result_argv_string = ""
			});
		}

		// test with a lot af argument
		{
			test_env_option_i((t){
				.nb_test = 4,
				.nb_line = L,
				.argv_string = "TERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.hXzIDZD3Au/Listeners ""LC_TERMINAL_VERSION=3.3.2 ""Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.TgxKXCRc5M/Render ""COLORFGBG=7;0 ""ITERM_PROFILE=Default ""XPC_FLAGS=0x0 ""LANG=en_US.UTF-8 ""PWD=/Users/adpusel/setting_software ""SHELL=/bin/zsh ""TERM_PROGRAM_VERSION=3.3.2 ""TERM_PROGRAM=iTerm.app ""PATH=/Users/adpusel/.brew/bin:/Users/adpusel/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Applications/VMware ""LC_TERMINAL=iTerm2 ""COLORTERM=truecolor ""TERM=xterm-256color ""HOME=/Users/adpusel ""TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000381m000t0d/T/ ""USER=adpusel ""XPC_SERVICE_NAME=0 ""LOGNAME=adpusel ""ITERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""__CF_USER_TEXT_ENCODING=0x680D:0x0:0x0 ""SHLVL=1 ""OLDPWD=/Users/adpusel/setting_software ""ZSH=/Users/adpusel/.oh-my-zsh ""PAGER=less ""LESS=-R ""LC_CTYPE=en_US.UTF-8 ""LSCOLORS=Gxfxcxdxbxegedabagacad ""_=/usr/bin/env",
				.result_int = OK,
				.result_env_string = "TERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.hXzIDZD3Au/Listeners ""LC_TERMINAL_VERSION=3.3.2 ""Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.TgxKXCRc5M/Render ""COLORFGBG=7;0 ""ITERM_PROFILE=Default ""XPC_FLAGS=0x0 ""LANG=en_US.UTF-8 ""PWD=/Users/adpusel/setting_software ""SHELL=/bin/zsh ""TERM_PROGRAM_VERSION=3.3.2 ""TERM_PROGRAM=iTerm.app ""PATH=/Users/adpusel/.brew/bin:/Users/adpusel/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Applications/VMware ""LC_TERMINAL=iTerm2 ""COLORTERM=truecolor ""TERM=xterm-256color ""HOME=/Users/adpusel ""TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000381m000t0d/T/ ""USER=adpusel ""XPC_SERVICE_NAME=0 ""LOGNAME=adpusel ""ITERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""__CF_USER_TEXT_ENCODING=0x680D:0x0:0x0 ""SHLVL=1 ""OLDPWD=/Users/adpusel/setting_software ""ZSH=/Users/adpusel/.oh-my-zsh ""PAGER=less ""LESS=-R ""LC_CTYPE=en_US.UTF-8 ""LSCOLORS=Gxfxcxdxbxegedabagacad ""_=/usr/bin/env ",
				.result_argv_string = ""
			});
		}

		// test with = at start
		{
			test_env_option_i((t){
				.nb_test = 5,
				.nb_line = L,
				.argv_string = "=heysalut comment=cava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "",
				.result_argv_string = "=heysalut comment=cava? hey=salut comment=cava?"
			});
		}

		// test with no = in the first element
		{
			test_env_option_i((t){
				.nb_test = 6,
				.nb_line = L,
				.argv_string = "heysalut comment=cava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "",
				.result_argv_string = "heysalut comment=cava? hey=salut comment=cava?"
			});
		}

		// test with no = in the second element
		{
			test_env_option_i((t){
				.nb_test = 7,
				.nb_line = L,
				.argv_string = "hey=salut commentcava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "hey=salut ",
				.result_argv_string = "commentcava? hey=salut comment=cava?"
			});
		}
	}

	/*
	* test option -u
	* */
	if (1)
	{
		//		// test with no argument and empty env
		//		{
		//			test_env_option_u((t){
		//				.nb_test = 8,
		//				.nb_line = L,
		//				.env_string = "",
		//				.argv_string = "",
		//				.result_int = OK,
		//				.result_env_string = "",
		//				.result_argv_string = ""
		//			});
		//		}

		// test with no argument and env
		{
			test_env_option_u((t){ .nb_test = 9, .nb_line = L,
				.env_string = "minh=jolie toto=titi ",
				.argv_string = "",
				.result_int = OK,
				.result_env_string = "minh=jolie toto=titi ",
				.result_argv_string = ""
			});
		}

		// delete first
		{
			test_env_option_u((t){ .nb_test = 10, .nb_line = L,
				.env_string = "minh=jolie toto=titi ",
				.argv_string = "-u minh",
				.result_int = OK,
				.result_env_string = "toto=titi ",
				.result_argv_string = ""
			});
		}

		// delete second
		test_env_option_u((t){ .nb_test = 10, .nb_line = L,
			.env_string = "minh=jolie toto=titi ",
			.argv_string = "-u toto",
			.result_int = OK,
			.result_env_string = "minh=jolie ",
			.result_argv_string = ""
		});

		// delete big and multiple
		test_env_option_u((t){ .nb_test = 11, .nb_line = L,
			.env_string = "TERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.hXzIDZD3Au/Listeners ""LC_TERMINAL_VERSION=3.3.2 ""Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.TgxKXCRc5M/Render ""COLORFGBG=7;0 ""ITERM_PROFILE=Default ""XPC_FLAGS=0x0 ""LANG=en_US.UTF-8 ""PWD=/Users/adpusel/setting_software ""SHELL=/bin/zsh ""TERM_PROGRAM_VERSION=3.3.2 ""TERM_PROGRAM=iTerm.app ""PATH=/Users/adpusel/.brew/bin:/Users/adpusel/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Applications/VMware ""LC_TERMINAL=iTerm2 ""COLORTERM=truecolor ""TERM=xterm-256color ""HOME=/Users/adpusel ""TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000381m000t0d/T/ ""USER=adpusel ""XPC_SERVICE_NAME=0 ""LOGNAME=adpusel ""ITERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""__CF_USER_TEXT_ENCODING=0x680D:0x0:0x0 ""SHLVL=1 ""OLDPWD=/Users/adpusel/setting_software ""ZSH=/Users/adpusel/.oh-my-zsh ""PAGER=less ""LESS=-R ""LC_CTYPE=en_US.UTF-8 ""LSCOLORS=Gxfxcxdxbxegedabagacad ""_=/usr/bin/env",
			.argv_string = "-u LESS",
			.result_int = OK,
			.result_env_string ="TERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.hXzIDZD3Au/Listeners ""LC_TERMINAL_VERSION=3.3.2 ""Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.TgxKXCRc5M/Render ""COLORFGBG=7;0 ""ITERM_PROFILE=Default ""XPC_FLAGS=0x0 ""LANG=en_US.UTF-8 ""PWD=/Users/adpusel/setting_software ""SHELL=/bin/zsh ""TERM_PROGRAM_VERSION=3.3.2 ""TERM_PROGRAM=iTerm.app ""PATH=/Users/adpusel/.brew/bin:/Users/adpusel/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Applications/VMware ""LC_TERMINAL=iTerm2 ""COLORTERM=truecolor ""TERM=xterm-256color ""HOME=/Users/adpusel ""TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000381m000t0d/T/ ""USER=adpusel ""XPC_SERVICE_NAME=0 ""LOGNAME=adpusel ""ITERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""__CF_USER_TEXT_ENCODING=0x680D:0x0:0x0 ""SHLVL=1 ""OLDPWD=/Users/adpusel/setting_software ""ZSH=/Users/adpusel/.oh-my-zsh ""PAGER=less ""LC_CTYPE=en_US.UTF-8 ""LSCOLORS=Gxfxcxdxbxegedabagacad ""_=/usr/bin/env ",
			.result_argv_string = ""
		});

		// delete bad no element
		test_env_option_u((t){ .nb_test = 12, .nb_line = L,
			.env_string = "minh=jolie toto=titi ",
			.argv_string = "-u",
			.result_int = -1,
			.result_env_string = "minh=jolie toto=titi ",
			.result_argv_string = ""
		});

		// delete bad 2 element
		test_env_option_u((t){ .nb_test = 13, .nb_line = L,
			.env_string = "minh=jolie toto=titi ",
			.argv_string = "-u toto -u",
			.result_int = -1,
			.result_env_string = "minh=jolie ",
			.result_argv_string = ""
		});

		test_env_option_u((t){ .nb_test = 14, .nb_line = L,
			.env_string = "minh=jolie toto=titi ",
			.argv_string = "-u toto -u super -u holalala -u ",
			.result_int = -1,
			.result_env_string = "minh=jolie ",
			.result_argv_string = ""
		});
	}

	/*
	* test handle option
	* */
	{
		// test work with -u, -i and bad option

		// test -i good
		{
			g_test = 1;
			test_handle_option((t){ .nb_test = 14, .nb_line = L,
				.env_string = "minh=jolie toto=titi ",
				.argv_string = "-i minh=belle",
				.result_int = OK,
				.result_error_string = ""
			});

			test_handle_option((t){ .nb_test = 15, .nb_line = L,
				.env_string = "minh=jolie toto=titi ",
				.argv_string = "-u ",
				.result_int = -1,
				.result_error_string = "usage: env [-i] [name=value ...] [-u name]\n"
									   "          [utility [argument ...]]"
			});

			test_handle_option((t){ .nb_test = 15, .nb_line = L,
				.env_string = "minh=jolie toto=titi ",
				.argv_string = "-aou ",
				.result_int = -1,
				.result_error_string = "usage: env [-i] [name=value ...] [-u name]\n"
									   "          [utility [argument ...]]"
			});
		}
	}
}