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

#include <minishell.stuctures.h>
#include "libft.h"

char *get__argv_current(t_array *argv)
{
	return (
		*(char **)ftarray__current(argv)
	);
}

char *get__argv_at(t_array *argv, int index)
{
	return (
		*(char **)ftarray__at(argv, index)
	);
}

char *get__argv_next(t_array *argv)
{
	if (ftarray__next(argv))
		return (get__argv_current(argv));
	else
		return (NULL);
}

t_array *get__env(t_ms *ms)
{
	if (ms->env_tmp)
		return (ms->env_tmp);
	else
		return (ms->env);
}