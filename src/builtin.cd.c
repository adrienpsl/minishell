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

#include <errno.h>
#include "minishell.h"


// err to handle with access:
// f_ok / exist , r_ok write access, xok > execution

// are update at all cd
// PWD=/Users/adpusel/Applications
// OLDPWD=/Users/adpusel
// OLDPWD= PWD at start ?

// if unset Home and -, or ~ ?

// si je donne 2 argument a cd, il va remplacer le premier argv
// par le deuxieme dans le path tout le path, ca peut etre


// 1 if no operand && home is set >> go to home
// if not HOME do nothing
// if start . >
// if start / >

// if more one argv, I search where the pwd start and rewrite url before
// that point.


// cd -- = cd ~, cd -- > no option
// cd -

// check if the first arlsgv is -- or - > go home
// when I move, I need to keep my last path
// I need my current directory to go use relative path
// if start with . > relative path

// cd hadle the quotes

// un buffer de la size max,

// is - --

// build un errno pour y mettre mes error.


static int handle_if_relative_path(t_ms *ms, char *p_path)
{
	char *path;
	size_t i;

	path = ms->curpath;
	i = 0;
	if (p_path[0] == '.')
	{
		ft_mem_copy(path, ms->pwd, STRING_MODE);
		ft_str_len(&i, path);
		path[i++] = '/';
	}
	ft_mem_copy((path + i), p_path, STRING_MODE);
	return (0);
}

static int set_last_path(t_ms *ms)
{
	char *old_path;

	old_path = ms_get_env_value("OLDPATH", ms->p_env);
	if (!old_path)
		return (set_ft_errno(PATH_HAS_BE_DELETED));
	ft_mem_copy(ms->curpath, old_path, STRING_MODE);
	return (0);
}

int ms_cd(t_ms *ms)
{
	int i;
	char **arg;

	arg = ms->arg;
	if (!ms->arg)
		return (0);
	i = ft_str_split_count(ms->arg);
	if (i == 0)
		return (0);
	if (getcwd(ms->pwd, 4096) == NULL)
		return (set_ft_errno(EACCES));
	if (!ft_str_eq(*arg, "--") && arg++ && i--)
		(void) "this is a line that I need to fill :)";
	if (!ft_str_eq(*arg, "-"))
		return (set_last_path(ms));
	else if (i == 1)
		return (handle_if_relative_path(ms, *arg));
	else if (i == 2)
	{
		if (!ft_search_and_replace(ms->pwd, arg[0], arg[1])
			&& !ft_mem_copy(ms->curpath, ms->pwd, STRING_MODE))
			return (0);
		else
			return (set_ft_errno(STR_NOT_IN_PATH));
	}
	return (set_ft_errno(E2BIG));
}