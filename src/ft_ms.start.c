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
**	split and prepare all data of a single command, between ;
**	and free after it, if the builtin exit is trigger, stop the execution of
**	the binary.
*/

static int		ms__command(char *line, char ***env)
{
	char			**command_spit;
	int				ret;
	static t_env	e = {0, 0};

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
**	chose the right getter for the user current line, in purpose to use or not
**	the canonical mode. split after that the current line.
*/

static int		get_line_user(char **env, char ***output)
{
	char	*line;
	int		res;

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

/*
**	perform on each line (of ; split):
**	- replace the builtin $ and ~
**	- launch the command
**	- free the data
**	if command return something, exit is trigger and the loop is done
*/

static int		loop_on_command(char **split_command, char ***env)
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

/*
**	this is the main loop of the binary, it will stop only if exit is trigger
**	print prompt, get user input and free
*/

int				ms__init(char ***env)
{
	char **command;

	print_prompt();
//	loop_on_command(ft_strsplit("setenv PATH=/Users/adpusel/code/42/minishell_new/test_prg", ";"), env);
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
