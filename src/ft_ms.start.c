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

static int get_command_split(t_env *e, char ***output, int test)
{
	char *line;
	int res;

	if (test == 0)
		res = ms__get_line((void *)e->env, g_line, &line);
	else
		res = get_line_test(g_line, &line);
	if (res == OK
		&& OK == replace_dollar_tilde((void *)e->env, line, &line))
	{
		*output = ft_strsplit(line, ";");
		ftstr__free(&line);
		if (*output)
			return (OK);
	}
	return (-1);
}

int ms__init(t_env *e, int test)
{
	char **command;

	print_prompt();
	while (OK == get_command_split(e, &command, test))
	{
		if (-1 != ft_strsplit_search(command, (void *)ms__command, e))
			break;
		print_prompt();
		ft_strsplit_free(&command);
	}
	ft_strsplit_free(&command);
	return (OK);
}
