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
**	if the **line is '~', search and add to new_line the HOME env value
**	move +1 *line
*/

static int replace_tilde(char **line, char **new_line, char **env)
{
	if (line[0][0] == '~')
	{
		ft_pstrjoin(*new_line,
			ms__env_get_value(env, "HOME", find_variable),
			1,
			new_line);
		*line += 1;
		return (1);
	}
	return (0);
}

/*
**	will build a new line (witch will be put in *output)
**	compose by the env key corresponding at 'HOME' for ~ 
**	and the shell variable $[a-zA-z_]+ of the line
**	if there is no data in env to match the variable,
**	no error is raise.
*/

int replace_dollar_tilde(const char **env, char *line, char **output)
{
	char *new_line;

	if (NULL == (new_line = ft_memalloc(1)))
		return (-1);
	while (*line != '\0')
	{
		if (0 == ms_replace_dollar(&line, &new_line, (char **)env)
			&& 0 == replace_tilde(&line, &new_line, (char **)env))
		{
			ft_pstrjoin_chr(new_line, *line, 1, &new_line);
			line += 1;
		}
	}
	*output = new_line;
	return (OK);
}
