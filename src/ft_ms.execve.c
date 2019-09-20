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
	free(path);
	return (0);
}

int ms__handle_binary(char **argv, char **env)
{
	char *path;

	path = (*argv && **argv == '/')
		   ? ft_strdup(*argv) : ms__search_binary(env, *argv);
	if (path == NULL)
		return (-1);
	else if (OK != ftsystm__test_file(path, MS__NAME, *argv))
		return (-1);
	else
		return (exec_binary(path, argv, env));
}

t_func find_funct(char *name)
{
	static t_element_func g_func[5] = {
		{ "setenv",   ms__setenv },
		{ "unsetenv", ms__unset_env },
		{ "cd",       ms__cd },
		{ "echo", NULL },
		{ "exit", NULL }
	};
	int i;

	i = 0;
	while (i < 5)
	{
		if (OK == ft_strcmp(g_func[i].name, name))
			return (g_func[i].func);
		i++;
	}
	return (NULL);
}

int ms__dipatch(char *line, char **env)
{
	int i;
	char **argv;
	t_env_ret *ret;

	if ('\0' == line)
		return (OK);
	if (NULL == (argv = ft_strsplit(line, " ")))
		return (-1);
	if (argv)
	{
		if (OK == ft_strcmp("env", *argv))

	}

	ft_strsplit_free(&argv);
	return (OK);
}
