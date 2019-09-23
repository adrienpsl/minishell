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

/*
** @brief	:will try to go to the directory that is at full_path,
**			 and ft_printf the error if it appears
** @param	 full_path the path of the directory
** @param	:argv can be path or relative path, in purpose of log the error
**			 according to the zsh CD command
** @return	:ok => 0 || ko => -1
*/
static int	test_and_chdir(char *full_path, char *argv)
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

/*
** @brief		:- will transform the argv in full path, if it relative.
**				 - test and chdir with the func test_and_chdir
**				 - print the path according to the CD zsh's builtin
** @param path	: path for the chdir system function
** @param print	: if true, will print the new pwd
** @return		: ok => 0 || ko => -1
*/
int			cd__change_directory(char *path, int print)
{
	int		ret;
	char	*full_path;

	if (!path)
		return (-1);
	if (path[0] != '/')
	{
		full_path = ft_strjoin("/", path, 0);
		full_path = ft_strjoin(ftsystm__get_current_path(), full_path, 2);
	}
	else
		full_path = path;
	ret = test_and_chdir(path, path);
	if (OK == ret && TRUE == print)
		ft_printf("%s\n", ftsystm__get_current_path());
	if (full_path != path)
		ftstr__free(&full_path);
	return (ret);
}
