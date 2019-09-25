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

/*
**	- find the binary in path if it's a command
**	- if find the binary and I have right launch the program
*/
static int find_and_launch_binary(char **argv, char ***env)
{
	const char *path;
	int ret;

	if (!argv || !*argv || !env)
		return (-1);
	path = (**argv == '/') ? *argv : ms__search_binary(*env, *argv);
	if (path == NULL)
	{
		ft_printf(MS__NAME"command not found: %s\n", *argv);
		return (-1);
	}
	if (OK == ftsystm__test_file((char *)path, "minishell", *argv))
		ret = exec_binary((char *)path, argv, *env);
	else
		ret = -1;
	if (path != *argv)
		ftstr__free((char **)&path);
	return (ret);
}

int loop_on_env(t_data *d, t_env *e)
{
	while (OK == ft_strcmp("env", *d->argv))
	{
		d->argv += 1;
		if (OK != ms__env(d, e))
			return (d->ret);
	}
	return (OK);
}

/*
**	that function recursive until the end of the env stuff,
**	and after return
*/
int dispatch_between_binary_and_builtin(t_data *d, t_env *e)
{
	if (OK == ft_strcmp("exit", *d->argv))
		return (MS__EXIT);
	if (OK != loop_on_env(d, e))
		return (d->ret);
	if (NULL == *d->argv)
		return (OK);
	else if (OK == ft_strcmp("setenv", *d->argv))
		return (ms__setenv(d->argv, get_env(e)));
	else if (OK == ft_strcmp("unsetenv", *d->argv))
		return (ms__unsetenv(d->argv, get_env(e)));
	else if (OK == ft_strcmp("unsetenv", *d->argv))
		return (ms__unsetenv(d->argv, get_env(e)));
	else if (OK == ft_strcmp("echo", *d->argv))
		return 2;
	else
		return (find_and_launch_binary(d->argv, get_env(e)));
}

int ms__command(char *line, t_env *e)
{
	char **start;
	t_data d;

	ft_bzero(&d, sizeof(t_data));
	if ('\0' == *line)
		return (OK);
	if (NULL == (d.argv = ft_strsplit(line, " ")))
		return (-1);
	start = d.argv;
	d.ret = dispatch_between_binary_and_builtin(&d, e);
	ft_strsplit_free(&e->tmp_env);
	ft_strsplit_free(&start);
	return (d.ret);
}
