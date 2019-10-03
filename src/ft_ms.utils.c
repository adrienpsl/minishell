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

char			*ms__search_binary(
	char **env,
	char *binary_name,
	int (*f)(char *, char *))
{
	char *path;
	char *found;

	if (NULL != (path = ms__env_get_value((char **)env, "PATH", find_variable)))
	{
		found = ftsystm__find_in_path(path, ":", binary_name, f);
		return (found);
	}
	return (NULL);
}

void			print_prompt(void)
{
	ft_printf("\n%s:\n$> ", ftsystm__get_current_path());
}

int				ms__echo(char **argv, char ***env)
{
	int new_line;

	if (OK == ft_strcmp("-n", *argv))
	{
		new_line = 0;
		argv += 1;
	}
	else
		new_line = 1;
	ft_strsplit_print(argv, ' ');
	if (new_line)
		ft_printf("\n");
	return (OK);
	(void)env;
}

/*
**	transfer all the user line to g_line
*/

int				get_line_test(
	t_s *const line,
	char **output)
{
	static char		buffer[2];
	int				ret;

	fts__clear(line);
	ft_bzero(buffer, 2);
	while ((ret = read(0, buffer, 1)) > 0)
	{
		if (-1 != ft_strchr_int(buffer, '\n'))
			break ;
		fts__add(line, buffer);
		ft_bzero(buffer, 1);
	}
	if (ret <= 0)
		return (-1);
	ft_printf("%s\n", line->data);
	*output = line->data;
	return (OK);
}
