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

#include <minishell.defines.h>
#include "ft_ms.cd.h"

char *one_and_zero_argv(char *argv, char **env)
{
	char *path;
	char *key;

	if (NULL == argv || OK == ft_strcmp("-", argv))
	{
		key = (argv == NULL) ? "HOME" : "OLDPATH";
		path = ms__get_value(env, key);
		if (path == NULL)
			ft_printf(MS__NAME"line %d: cd: %s not set\n", __LINE__, key);
	}
	else
		path = ft_strdup(argv);
	return (path);
}

char *two_argument(char *argv[2])
{
	char *current_path;
	char *new_path;

	current_path = ftsystm__get_current_path();
	if (NULL != current_path)
	{
		new_path = ftstr__replace_str(current_path, argv[0], argv[1]);
		if (new_path)
			return (new_path);
		else
			ft_printf("cd: string not in pwd: %s\n", argv[0]);
	}
	return (NULL);
}

int test_and_go_dir(char *path, char *argv)
{
	if (OK != ftsystm__test_file(path, "cd", argv))
		return (-1);
	if (OK != chdir(path))
	{
		ft_printf("cd: not a directory: %s\n", argv);
		return (-1);
	}
	return (OK);
}

char *add_current_path(char *path)
{
	char *new_path;

	new_path = ft_strjoin("/", path, 2);
	new_path = ft_strjoin(ftsystm__get_current_path(), new_path, 2);
	return (new_path);
}

// il doit avoir un triple ptr sur env, et c'est lui qu
// que je passe a tout mes elements

//int ms__cd(char **argv, char  **env)
//{
//
//	if (*argv && OK == ft_str_cmp("--", *argv))
//		argv += 1;
////	if (OK != cd__serialize_path(argv, env, buffer, &print_new_path))
////		return (-1);
////	if (OK != cd_move_directory(buffer, env))
////		return (-1);
////	if (print_new_path)
////		ft_printf("%s\n", ftsystm__get_current_path());
////	fts__free(&buffer);
//	return (OK);
//}