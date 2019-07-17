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

#include "minishell.h"

static int ft_env_init(char ***argv, long *options, int *i, char ***env_save)
{
	*i = ft_str_split_count(*argv);
	*options = 0;
	if (*i && ***argv == '-')
	{
		if (ft_io_catch_options((**argv) + 1, "iu", options))
		{
			ft_printf("env: bad option given ! \n");
			return (-1);
		}
		if (*i == 1)
		{
			ft_printf("env: option requires an argument ! \n");
			return (-1);
		}
		(*argv)++;
	}
	*env_save = m.env;
	return (0);
}

// if 1


// if 2

// je save la variable path a un endroit donner,
// car c'est elle qui me permet d'aller dans les programme ?

void ft_env(char **argv)
{
	int i;
	long options;
	char **env_save;

	if (ft_env_init(&argv, &options, &i, &env_save))
		return;
	if (options & 1
		&& !(m.env = ft_str_split("", " ")))
		return;
	else if (options & 2
			 && !(m.env = ms_unset_env(*argv, m.env)))
		return;
	if (!*argv)
		ft_strsplit_print(m.env, '\n');
	else
		ms_do_cmd(argv);
	if (m.env)
		ft_str_split_free(&m.env);
	m.env = env_save;
}
