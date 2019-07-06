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
// is
int build_path(t_ms *ms, char *p_path)
{
	char *path;
	size_t i;

	path = ms->curpath;
	ft_mem_set(path, 0, 4096);
	i = 0;
	if (p_path[0] == '.')
	{
		// TODO : handle that error;
		ft_mem_copy(path, ms->pwd, STRING_MODE);
		ft_str_len(&i, path);
		path[i++] = '/';
	}
	ft_mem_copy((path + i), p_path, STRING_MODE);
	return (0);
}

// do check
int init_cd(t_ms *ms, int i)
{
	// get with function where I am,
	if (getcwd(ms->pwd, 4096) == NULL)
		// TODO :  set error get current directory
		return (-1);
	if (i == 2)
	{
		// do a search an replace here
		// TODO : set error not in pwd + error logs
	}
	return (0);
}

int ms_cd(t_ms *ms)
{
	int i;
	i = ft_str_split_count(ms->arg);


	// I need that
	// I want do the check here

	// get the env path ?
	// each return if need error handling ?

	// if no option

	// if one option

	// if 2 options
	// build path

}