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
#include <ft_mem.h>

static int replace_dollar(const char *current, char **new_line, char **env)
{
	char *key;
	int length;
	char *value;

	if (current[0] == '$'
		&& current[1] != ' '
		&& current[1] != '\0')
	{
		length = ft_strchr_int((char *)current + 1, ' ');
		if (length == -1)
			length = ft_strlen((char *)current + 1);
		key = ft_strndup(current + 1, length);
		if (key)
		{
			value = ms__env_get_value(env, key);
			ft_pstrjoin(*new_line, value ? value : "", 1, new_line);
			ftstr__free(&key);
		}
		return (length + 1);
	}
	return (0);
}

static int replace_tilde(const char *current, char **new_line, char **env)
{
	if (current[0] == '~')
	{
		ft_pstrjoin(*new_line, ms__env_get_value(env, "HOME"), 1, new_line);
		return (1);
	}
	return (0);
}

int replace_dollar_tilde(
	const char **env,
	const char **line)
{
	const char *current;
	char *new_line;
	int size;

	if (NULL == (new_line = ft_memalloc(1)))
		return (-1);
	current = *line;
	while (*current != '\0')
	{
		if ((size = replace_dollar(current, &new_line, (char **)env)))
			current += size;
		else if ((size = replace_tilde(current, &new_line, (char **)env)))
			current += size;
		else
		{
			ft_pstrjoin_chr(new_line, *current, 1, &new_line);
			current += 1;
		}
	}
	ftstr__free((char **)line);
	*line = new_line;
	return (OK);
}
