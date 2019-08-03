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
#include "libft.h"

void signal_program(int t)
{
	(void) t;
	ft_printf("\n");
}

void ms_print_prompt()
{
	char current_pwd[MS_SIZE_BUFFER_FULL];
	char *home;
	char *replace;

	if (!getcwd(current_pwd, MS_SIZE_BUFFER_FULL - 1))
		return ;
	home = ms_get_value("HOME");
	replace = ft_str_replace(current_pwd, home, "~", 0);
	if (replace)
	{
		ft_printf("\n%s\n$> ", replace);
		free(replace);
	}
}

void signal_minishell(int sign)
{
	(void) sign;
	g_ms.ctrlc = 1;
	ft_str_free(&g_ms.line);
	ft_printf("\n");
	ms_print_prompt();
}

int ms_put_in_buffer(char *buffer, char *str)
{
	if (ft_strlen(str) >= MS_SIZE_BUFFER)
		return (ft_put_int(-1, MS_BUFFER_ERROR));
	ft_strcat(buffer, str);
	return (0);
}

// will return stuff if execution, are trigger.
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
