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
#include <minishell.prototypes.h>
#include <minishell.defines.h>

static int exec_binary(char *path, char **argv, char **env)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, ms_signal_exec);
	if (pid == 0)
		execve(path, argv, env);
	if (pid > 0)
		wait(&pid);
	if (pid < 0)
	{
		ft_printf(MS__NAME" binary exec fail");
		return (-1);
	}
	signal(SIGINT, ms_signal_minishell);
	return (0);
}

static int find_and_check_binary(char **argv, char ***env)
{
	char *path;

	path = (*argv && **argv == '/')
		   ? ft_strdup(*argv) : ms__search_binary(*env, *argv);
	if (path == NULL && *argv && **argv != '/')
		ft_printf(MS__NAME"command not found: %s\n", *argv);
	if (path == NULL)
		return (-1);
	if (OK != ftsystm__test_file(path, MS__NAME, *argv))
		return (-1);
	exec_binary(path, argv, *env);
	free(path);
	return (OK);
}

static t_func find_function(char *name)
{
	static t_element_func g_func[5] = {
		{ "setenv",   ms__setenv },
		{ "unsetenv", ms__unset_env },
		{ "cd",       ms__cd },
		{ "echo", NULL },
	};
	int i;

	i = 0;
	while (i < 5)
	{
		if (OK == ft_strcmp(g_func[i].name, name))
			return (g_func[i].func);
		i++;
	}
	return (find_and_check_binary);
}

static int loop_and_recursive(char **argv, char ***env)
{
	t_env_ret *ret;

	ret = NULL;
	if (OK == ft_strcmp("env", *argv))
	{
		if (NULL != (ret = ms__env(argv, *env))
			&& NULL != ret->env)
			loop_and_recursive(ret->argv, &ret->env);
	}
	else if (OK == ft_strcmp("exit", *argv) && NULL == ret)
		return (2);
	else
		find_function(*argv)(argv, env);
	if (ret->env)
		ft_strsplit_free(&ret->env);
	return (OK);
}

int ms__command(char *line, char ***env)
{
	char **argv;
	int ret;

	if ('\0' == line)
		return (OK);
	if (NULL == (argv = ft_strsplit(line, " ")))
		return (-1);
	ret = loop_and_recursive(argv, env);
	ft_strsplit_free(&argv);
	return (ret);
}
