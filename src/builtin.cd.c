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

static int one_argv(t_ms *ms, char *p_path)
{
	char *path;
	size_t i;

	path = ms->cur_path;
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

static int two_argv(t_ms *ms, char **arg)
{
	if (!ft_str_replace(ms->pwd, arg[0], arg[1])
		&& !ft_mem_copy(ms->cur_path, ms->pwd, STRING_MODE))
		return (0);
	else
		return (set_ft_errno(STR_NOT_IN_PATH, arg[0], ms));
}

static int get_path_env(t_ms *ms, char *name_env, int error)
{
	char *old_path;

	old_path = ms_get_env_value(name_env, ms->p_env);
	if (!old_path)
		return (set_ft_errno(error, NULL, NULL));
	ft_mem_copy(ms->cur_path, old_path, STRING_MODE);
	return (0);
}

static int init_cd(t_ms *ms, int *i, char ***arg)
{
	if (!ms->arg)
		return (-1);
	*arg = ms->arg;
	*i = ft_str_split_count(*arg);
	if (getcwd(ms->pwd, 4096) == NULL)
		return (set_ft_errno(EACCES, "", ms));
	if (ft_str_is(**arg, "--"))
	{
		(*arg)++;
		(*i)--;
	}
	return (0);
}

int ms_cd(t_ms *ms)
{
	int i;
	int ret;
	char **arg;

	if (init_cd(ms, &i, &arg))
		return (-1);
	if (i == 0)
		ret = get_path_env(ms, "HOME", HOME_HAS_BE_DELETED);
	else if (ft_str_is(*arg, "-"))
		ret = get_path_env(ms, "OLDPATH", OLDPATH_HAS_BE_DELETED);
	else if (i == 1)
		ret = one_argv(ms, *arg);
	else if (i == 2)
		ret = two_argv(ms, arg);
	else
		ret = set_ft_errno(E2BIG, "", ms);
	return (ret);
}