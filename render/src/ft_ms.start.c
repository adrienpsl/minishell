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

int ms__command(char *line, char ***env)
{
	char **command_spit;
	int ret;
	t_env e = {0, 0};

	e.env = env;
	if ('\0' == *line)
		return (OK);
	if (NULL == (command_spit = ft_strsplit(line, " ")))
		return (-1);
	ret = ms__dispatch(command_spit, &e);
	ft_strsplit_free(&e.tmp_env);
	ft_strsplit_free(&command_spit);
	return (ret == MS__EXIT ? 1 : 0);
}

/*
**	line is a part of fts so I do not free it
*/
static int get_line_user(char **env, char ***output)
{
	char *line;
	int res;

	if (g_ms_test == 1)
		res = get_line_test(g_line, &line);
	else
		res = ms__get_line(env, g_line, &line);
	if (res == OK)
	{
		*output = ft_strsplit(line, ";");
		if (*output)
			return (OK);
	}
	return (-1);
}

static int loop_on_command(char **split_command, char ***env)
{
	char *new_line;

	while (*split_command != NULL)
	{
		if (OK != replace_dollar_tilde(*env,
			*split_command,
			&new_line))
			return (-1);
		if (ms__command(new_line, env))
			return (1);
		ftstr__free(&new_line);
		split_command += 1;
	}
	return (OK);
}

int ms__init(char ***env)
{
	char **command;

	print_prompt();
	while (OK == get_line_user(*env, &command))
	{
		if (OK != loop_on_command(command, env))
			break ;
		print_prompt();
		ft_strsplit_free(&command);
	}
	ft_strsplit_free(&command);
	return (OK);
}
