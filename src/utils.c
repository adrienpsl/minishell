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

void ms_print_prompt(int new_line)
{
	char current_pwd[MS_SIZE_BUFFER_FULL];
	char *home;
	char *replace;

	if (!getcwd(current_pwd, MS_SIZE_BUFFER_FULL - 1))
		return;
	home = ms_get_value("HOME");
	replace = ft_str_replace(current_pwd, home, "~", 0);
	if (replace)
	{
		if (new_line == MS_BEFORE)
			ft_printf("\n");
		ft_printf("\n%s\n$> ", replace);
		free(replace);
		if (new_line == MS_AFTER)
			ft_printf("\n");
	}
}

int ms_test_file(char *builtin, char *path)
{
	if (!path || access(path, F_OK))
	{
		ft_printf("%s: no such file or directory: %s\n", builtin, path);
		return (-1);
	}
	if (access(path, R_OK))
	{
		ft_printf("%s: permission denied: %s\n", builtin, path);
		return (-1);
	}
	if (access(path, X_OK))
	{
		ft_printf("%s: execution denied: %s\n", builtin, path);
		return (-1);
	}
	return (0);
}
