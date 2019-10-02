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

#include <minishell.h>

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

static int find_binary(char **argv, char **env, char **path)
{
	int ret;

	*path = (**argv == '/') ?
			ft_strdup(*argv) :
			ms__search_binary(env, *argv, ftstr__search_start_strict);
	if (*path == NULL)
	{
		ft_printf(MS__NAME"command not found: %s\n", *argv);
		return (-1);
	}
	ret = ftsystm__test_file(*path, "minishell", *argv);
	if (OK != ret)
		ftstr__free(path);
	return (ret);
}

static int handle_builtin(char **argv, char ***env, int *ret)
{
	int i;
	static char *name[5] = { "cd", "setenv", "unsetenv", "echo", NULL };
	static t_func func[5] = { ms__cd, ms__setenv, ms__unsetenv, ms__echo, NULL };

	if (-1 < (i = ft_strsplit_search(name, (void *)ft_streq, *argv)))
	{
		*ret = func[i](++argv, env);
		return (1);
	}
	return (0);
}

int ms__dispatch(char **argv, t_env *e)
{
	int ret;
	char *path;

	if (OK == ft_strcmp("exit", *argv))
		return (MS__EXIT);
	if (OK == ft_strcmp("env", *argv))
	{
		if (OK != ms__env(&argv, e))
			return (-1);
	}
	if (NULL == *argv)
		return (OK);
	if (OK != handle_builtin(argv, get_env(e), &ret))
		return (ret);
	else
	{
		if (OK == find_binary(argv, *get_env(e), &path))
		{
			exec_binary(path, argv, *get_env(e));
			ftstr__free(&path);
			return (OK);
		}
		return (-1);
	}
}
