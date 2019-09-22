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
	if (OK != ftsystm__test_file(path, "minishell", *argv))
		return (-1);
	exec_binary(path, argv, *env);
	free(path);
	return (OK);
}

static int ms__dispatch_good_binary(char **argv, char ***env)
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
		if (OK == ft_strcmp(g_func[i].name, *argv))
			return (g_func[i].func(++argv, env));
		i++;
	}
	return (find_and_check_binary(argv, env));
}

/*
**	that function recursive until the end of the env stuff,
**	and after return
*/
static int loop_and_recursive(char **argv, char ***env)
{
	t_env_ret *ret;
	int result;

	ret = NULL;
	if (OK == ft_strcmp("env", *argv))
	{
		if (NULL != (ret = ms__env(++argv, *env))
			&& NULL != ret->env)
			result = loop_and_recursive(ret->argv, &ret->env);
		else
			result = OK;
	}
	else if (OK == ft_strcmp("exit", *argv) && NULL == ret)
		result = MS__EXIT;
	else
		result = ms__dispatch_good_binary(argv, env);
	if (ret && ret->env)
		ft_strsplit_free(&ret->env);
	return (result);
}

int ms__command(char *line, char ***env)
{
	char **argv;
	char **start;
	int ret;

	if (line && '\0' == *line)
		return (OK);
	if (NULL == (argv = ft_strsplit(line, " ")))
		return (-1);
	start = argv;
	ret = loop_and_recursive(argv, env);
	ft_strsplit_free(&start);
	return (ret);
}
