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

void ms_cd_print_error(t_ms *ms, char *builtin)
{
	if (ms->error)
	{
		ft_str_put_fd(builtin, 2)
		&& ft_str_put_fd(" : ", 2);
		if (ms->error == HOME_HAS_BE_DELETED)
			ft_str_put_fd("HOME ENV HAS BEEN DELETE", 2);
		else if (ms->error == OLDPATH_HAS_BE_DELETED)
			ft_str_put_fd("OLDPATH HAS BEEN DELETE", 2);
		else if (ms->error == STR_NOT_IN_PATH)
			ft_str_put_fd("string not in pwd: ", 2)
			&& ft_str_put_fd("string not in pwd: ", 2);
	}
}
