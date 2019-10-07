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

/*
**	fork the program, and set at the fork, an new SIGINT handler,
**	to avoid a multiple print prompt, reset the classic handle after that
*/

static int		exec_binary(char *path, char **argv, char **env)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, ms_signal_exec);
	if (pid == 0)
	{
		if (-1 == execve(path, argv, env))
		{
			ft_printf("the file is not a valid binary\n");
			return (-2);
		}
	}
	if (pid > 0)
		wait(&pid);
	if (pid < 0)
	{
		ft_printf(MS__NAME" binary exec fail\n");
		return (-1);
	}
	signal(SIGINT, ms_signal_minishell);
	return (0);
}

/*
**	find the path binary if the argv is a command
**	and return : if the binary is valid
*/

static int		find_binary(char **argv, char **env, char **path)
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
	ret = ftsystm__check_file(*path, "minishell", *argv)
		|| ftsystm_check_exe(*path, "minishell", *argv);
	if (OK != ret)
		ftstr__free(path);
	return (ret);
}

/*
**	dispatch among the builtin if the command is one
*/

static int		handle_builtin(char **argv, char ***env, int *ret)
{
	int				i;
	static char		*name[5] = { "cd", "setenv", "unsetenv", "echo", NULL };
	static t_func	func[5] = {
		ms__cd, ms__setenv, ms__unsetenv, ms__echo, NULL };

	if (-1 < (i = ft_strsplit_search(name, (void *)ft_streq, *argv)))
	{
		*ret = func[i](++argv, env);
		return (1);
	}
	return (0);
}

/*
**	find and pass binary to exc, if command fail, I exit the fork
*/

static int		launch_binary(char **argv, t_env *e)
{
	char	*path;

	if (OK == find_binary(argv, *get_env(e), &path))
	{
		if (-2 == exec_binary(path, argv, *get_env(e)))
		{
			ftstr__free(&path);
			exit(-2);
		}
		ftstr__free(&path);
		return (OK);
	}
	return (-1);
}

/*
**	dispatch the command to the right binary
*/

int				ms__dispatch(char **argv, t_env *e)
{
	int		ret;

	if (OK == ft_strcmp("exit", *argv))
		return (MS__EXIT);
	if (OK == ft_strcmp("env", *argv))
	{
		argv += 1;
		if (OK != ms__env(&argv, e))
			return (-1);
	}
	if (NULL == *argv)
		return (OK);
	if (OK != handle_builtin(argv, get_env(e), &ret))
		return (ret);
	else
		return (launch_binary(argv, e));
}
