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
	char *argv_string;
	char *env_string;
	//
	int result_int;
	char *result_env_string;
	char *result_argv_string;
} t;

void test_cmp_split_str(char *name, char *expected, char **returned)
{
	g_test = 1;
	test_clear_testbuff();
	ft_strsplit_print(returned, ' ');

	if (test_cmp_testbuff(expected))
	{
		printf("%s", name);
	}
	g_test = 0;
}

void test_cmp_env_str(char *name, char *expected, t_array *env)
{
	g_test = 1;
	test_clear_testbuff();
	ftarray__func(env, ms__print_env, NULL);

	if (test_cmp_testbuff(expected))
	{
		printf("%s", name);
	}
	g_test = 0;
}

void test_env_option_i(t t)
{
	// function data
	char **argv_start = ft_strsplit(t.argv_string, " ");
	char **argv = argv_start;

	//	char **split_tmp =  ft_strsplit(t.env_string, " ");
	//	t_array *sys_env = ms__parse_env(split_tmp);
	//	ft_strsplit_free(&split_tmp);

	// return function
	int function_return;
	t_array *env_tmp = NULL;

	// function call
	function_return = option_i(&argv, &env_tmp);

	// function result test
	if (t.result_int != function_return)
	{
		printf("error return : \n");
		printf("expected : %d \n", t.result_int);
		printf("returned : %d \n", function_return);
	}
	// function argv forward test
	test_cmp_split_str("argv forward", t.result_argv_string, argv);
	// function test env
	test_cmp_env_str("env test", t.result_env_string, env_tmp);

	// free function data
	ft_strsplit_free(&argv_start);
	//	ftarray__free_func(&sys_env, ms__func_free_env, NULL);

	// free function created data
	if (env_tmp)
		ftarray__free_func(&env_tmp, ms__func_free_env, NULL);
}

void test_ms__env()
{
	/*
	* test env_option_i
	* */
//	if (0)
	{
		// test with no param
		{
			test_env_option_i((t){
				.argv_string = "",
				.result_int = OK,
				.result_env_string = "",
				.result_argv_string = ""
			});
		}

		// test with one good param
		{
			test_env_option_i((t){
				.argv_string = "hey=salut",
				.result_int = OK,
				.result_env_string = "hey=salut\n",
				.result_argv_string = ""
			});
		}

		// test with two good param
		{
			test_env_option_i((t){
				.argv_string = "hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "hey=salut\ncomment=cava?\n",
				.result_argv_string = ""
			});
		}

		// test with 2x2 same argv
		{
			test_env_option_i((t){
				.argv_string = "hey=salut comment=cava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "hey=salut\ncomment=cava?\n",
				.result_argv_string = ""
			});
		}

		// test with a lot af argument
		{
			test_env_option_i((t){
				.argv_string = "TERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.hXzIDZD3Au/Listeners ""LC_TERMINAL_VERSION=3.3.2 ""Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.TgxKXCRc5M/Render ""COLORFGBG=7;0 ""ITERM_PROFILE=Default ""XPC_FLAGS=0x0 ""LANG=en_US.UTF-8 ""PWD=/Users/adpusel/setting_software ""SHELL=/bin/zsh ""TERM_PROGRAM_VERSION=3.3.2 ""TERM_PROGRAM=iTerm.app ""PATH=/Users/adpusel/.brew/bin:/Users/adpusel/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Applications/VMware ""LC_TERMINAL=iTerm2 ""COLORTERM=truecolor ""TERM=xterm-256color ""HOME=/Users/adpusel ""TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000381m000t0d/T/ ""USER=adpusel ""XPC_SERVICE_NAME=0 ""LOGNAME=adpusel ""ITERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C ""__CF_USER_TEXT_ENCODING=0x680D:0x0:0x0 ""SHLVL=1 ""OLDPWD=/Users/adpusel/setting_software ""ZSH=/Users/adpusel/.oh-my-zsh ""PAGER=less ""LESS=-R ""LC_CTYPE=en_US.UTF-8 ""LSCOLORS=Gxfxcxdxbxegedabagacad ""_=/usr/bin/env",
				.result_int = OK,
				.result_env_string = "TERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C\n""SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.hXzIDZD3Au/Listeners\n""LC_TERMINAL_VERSION=3.3.2\n""Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.TgxKXCRc5M/Render\n""COLORFGBG=7;0\n""ITERM_PROFILE=Default\n""XPC_FLAGS=0x0\n""LANG=en_US.UTF-8\n""PWD=/Users/adpusel/setting_software\n""SHELL=/bin/zsh\n""TERM_PROGRAM_VERSION=3.3.2\n""TERM_PROGRAM=iTerm.app\n""PATH=/Users/adpusel/.brew/bin:/Users/adpusel/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/Applications/VMware\n""LC_TERMINAL=iTerm2\n""COLORTERM=truecolor\n""TERM=xterm-256color\n""HOME=/Users/adpusel\n""TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000381m000t0d/T/\n""USER=adpusel\n""XPC_SERVICE_NAME=0\n""LOGNAME=adpusel\n""ITERM_SESSION_ID=w0t0p0:012F80B4-C00A-4328-B20D-4E865AC5599C\n""__CF_USER_TEXT_ENCODING=0x680D:0x0:0x0\n""SHLVL=1\n""OLDPWD=/Users/adpusel/setting_software\n""ZSH=/Users/adpusel/.oh-my-zsh\n""PAGER=less\n""LESS=-R\n""LC_CTYPE=en_US.UTF-8\n""LSCOLORS=Gxfxcxdxbxegedabagacad\n""_=/usr/bin/env\n",
				.result_argv_string = ""
			});
		}

		// test with = at start
		{
			test_env_option_i((t){
				.argv_string = "=heysalut comment=cava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "",
				.result_argv_string = "=heysalut comment=cava? hey=salut comment=cava?"
			});
		}

		// test with no = in the first element
		{
			test_env_option_i((t){
				.argv_string = "heysalut comment=cava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "",
				.result_argv_string = "heysalut comment=cava? hey=salut comment=cava?"
			});
		}

		// test with no = in the second element
		{
			test_env_option_i((t){
				.argv_string = "hey=salut commentcava? hey=salut comment=cava?",
				.result_int = OK,
				.result_env_string = "hey=salut\n",
				.result_argv_string = "commentcava? hey=salut comment=cava?"
			});
		}

	}

	/*
	* test
	* */
}