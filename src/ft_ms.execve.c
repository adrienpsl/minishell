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
static int find_and_check_binary(char **argv, char ***env)
{
	char *path;
	int ret;

	if (!argv || !*argv || !env)
		return (-1);
	path = (**argv == '/') ? *argv : ms__search_binary(*env, *argv);
	if (path == NULL)
	{
		ft_printf(MS__NAME"command not found: %s\n", *argv);
		return (-1);
	}
	if (OK == ftsystm__test_file(path, "minishell", *argv))
		ret = exec_binary(path, argv, *env);
	else
		ret = -1;
	if (path != *argv)
		ftstr__free(&path);
	return (ret);
}

static int ms__dispatch_good_binary(t_data *d, char ***env)
{
	int i;
	static t_element_func g_func[5] = {
		{ "setenv",   ms__setenv },
		{ "unsetenv", ms__unsetenv },
		{ "cd",       ms__cd },
		{ "echo", NULL },
	};

	if (!d->argv || !env)
		return (-1);
	i = 0;
	while (i < 5)
	{
		if (OK == ft_strcmp(g_func[i].name, *d->argv))
			break;
		i++;
	}
	if (i != 5)
	{
		d->argv += 1;
		d->ret = g_func[i].func(d->argv, env);
	}
	else
		d->ret = find_and_check_binary(d->argv, env);
	return (d->ret);
}

/*
**	that function recursive until the end of the env stuff,
**	and after return
*/
int loop_and_recursive(t_data *d, t_env *e)
{
	// si env stop or no
		while (OK == ft_strcmp("env", *d->argv))
	{
		d->argv += 1;
		if (OK != ms__env(d, e))
			return (d->ret);
	}
	if (OK == ft_strcmp("exit", *d->argv)
		&& NULL == e->tmp_env)
		d->ret = (MS__EXIT);
	else if (NULL != *d->argv)
		ms__dispatch_good_binary(d, get_env(e));
	ft_strsplit_free(&e->tmp_env);
	return (d->ret);
}

int ms__command(char *line, t_env *e)
{
	char **start;
	t_data d;

	ft_bzero(&d, sizeof(t_data));
	if (line && '\0' == *line)
		return (OK);
	if (NULL == (d.argv = ft_strsplit(line, " ")))
		return (-1);
	start = d.argv;
	loop_and_recursive(&d, e);
	ft_strsplit_free(&start);
	return (d.ret);
}
