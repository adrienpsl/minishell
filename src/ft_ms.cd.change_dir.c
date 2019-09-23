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

#include <minishell.prototypes.h>

static int test_and_go_dir(char *full_path, char *argv)
{
	if (!full_path || !argv)
		return (-1);
	if (OK != ftsystm__test_file(full_path, "cd", argv))
		return (-1);
	if (OK == chdir(full_path))
		return (OK);
	else
	{
		ft_printf("cd: not a directory: %s\n", argv);
		return (-1);
	}
}

static int add_current_path(char *argv)
{
	char *full_path;
	char ret;

	if (!argv)
		return (-1);
	full_path = ft_strjoin("/", argv, 0);
	full_path = ft_strjoin(ftsystm__get_current_path(), full_path, 2);
	ret = test_and_go_dir(full_path, argv);
	free(full_path);
	return (ret);
}

int cd__change_directory(char *argv, int print)
{
	int ret;

	if (!argv)
		return (-1);
	if (argv[0] != '/')
		ret = add_current_path(argv);
	else
		ret = test_and_go_dir(argv, argv);
	if (OK == ret && TRUE == print)
		ft_printf("%s\n", ftsystm__get_current_path());
	return (ret);
}
