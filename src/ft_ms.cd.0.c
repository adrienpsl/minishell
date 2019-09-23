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

int static is_old_path(char *argv)
{
	return (argv != NULL);
}

/*
** @brief					:try to replace in pwd with the user input, 
** @param argv				:input given by user 
** @param current_directory	:env of the minishell
** @return					:ok => 0 || ko => -1
*/
int			one_and_zero_argv(char *argv, char **env)
{
	char	*path;
	char	*key;

	if (env == NULL)
		return (-1);
	if (NULL == argv || OK == ft_strcmp("-", argv))
	{
		key = is_old_path(argv) ? "OLDPATH" : "HOME";
		path = ms__get_value(env, key);
		if (path == NULL)
		{
			ft_printf(MS__NAME"line %d: cd: %s not set\n", __LINE__, key);
			return (-1);
		}
		else
			return (cd__change_directory(path, is_old_path(argv)));
	}
	else
		return (cd__change_directory(argv, 0));
}

/*
** @brief					:try to replace in pwd with the user input, 
** @param argv				:input given by user 
** @param current_directory	:env of the minishell
** @return					:ok => 0 || ko => -1
*/
static int	two_argument(char *argv[2], char *current_directory)
{
	char	*new_path;

	if (argv == NULL || current_directory == NULL)
		return (-1);
	new_path = ftstr__replace_str(current_directory, argv[0], argv[1]);
	if (new_path)
		return (cd__change_directory(new_path, TRUE));
	else
	{
		ft_printf("cd: string not in pwd: %s\n", argv[0]);
		return (-1);
	}
}
/*
** @brief				:dispatch according to the size of argv
** @param argv			:input given by user
** @param env			:env of the minishell
** @param current_path	:env of the minishell
** @return				:ok => 0 || ko => -1
*/
static int	handle_argument(char **argv, char **env, char *current_path)
{
	int		size;

	size = ft_strsplit_count(argv);
	if (0 == size || 1 == size)
		return (one_and_zero_argv(*argv, env));
	else if (2 == size)
		return (two_argument(argv, current_path));
	else
	{
		ft_printf("cd: to much argument\n");
		return (-1);
	}
}

/*
** @brief		:Execute the builtin CD.
** @param argv	:input given by user
** @param env	:env of the minishell
** @return		:ok => 0 || ko => -1
*/
int			ms__cd(char **argv, char ***env)
{
	char	*current_path;
	int		ret;

	if (!argv || !env)
		return (-1);
	if (NULL == (current_path = ft_strdup(ftsystm__get_current_path())))
		return (-1);
	if (OK == ft_strcmp("--", *argv))
		argv += 1;
	if (OK == (ret = handle_argument(argv, *env, current_path)))
		ms__env_add(env, "OLDPATH", current_path);
	ftstr__free(&current_path);
	return (ret);
}
