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
	d.ret = ms__dispatch(&d, e);
	ft_strsplit_free(&e->tmp_env);
	ft_strsplit_free(&start);
	return (d.ret == MS__EXIT ? 1 : 0);
}

/*
**	line is a part of fts so I do not free it
*/
static int get_line_user(t_env *e, char ***output, int test)
{
	char *line;
	int res;

	if (test == 0)
		res = ms__get_line((void *)e->env, g_line, &line);
	else
		res = get_line_test(g_line, &line);
	if (res == OK)
	{
		*output = ft_strsplit(line, ";");
		if (*output)
			return (OK);
	}
	return (-1);
}

static int loop_on_command(char **split_command, t_env *e)
{
	char *new_line;

	while (*split_command != NULL)
	{
		if (OK != replace_dollar_tilde((void *)e->env,
			*split_command,
			&new_line))
			return (-1);
		if (ms__command(new_line, e))
			return (1);
		ftstr__free(&new_line);
		split_command += 1;
	}
	return (OK);
}

int ms__init(t_env *e, int test)
{
	char **command;

	print_prompt();
	while (OK == get_line_user(e, &command, test))
	{
		if (OK != loop_on_command(command, e))
			break;
		print_prompt();
		ft_strsplit_free(&command);
	}
	ft_strsplit_free(&command);
	return (OK);
}
