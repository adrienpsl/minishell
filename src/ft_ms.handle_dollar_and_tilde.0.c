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

static int replace_tilde(const char *current, char **new_line, char **env)
{
	if (current[0] == '~')
	{
		ft_pstrjoin(*new_line, ms__env_get_value(env, "HOME", find_variable), 1,
			new_line);
		return (1);
	}
	return (0);
}

int replace_dollar_tilde(
	const char **env,
	const char **line)
{
	char *current;
	char *new_line;
	int size;

	if (NULL == (new_line = ft_memalloc(1)))
		return (-1);
	current = (char *)*line;
	while (*current != '\0')
	{
//		if (replace_dollar(&current, &new_line, (char **)env))
//			current += size;
		if ((size = replace_tilde(current, &new_line, (char **)env)))
			current += size;
		else
		{
			ft_pstrjoin_chr(new_line, *current, 1, &new_line);
			current += 1;
		}
	}
	*line = new_line;
	return (OK);
}
