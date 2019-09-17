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

#include <ft_s.h>
#include "libft.h"

int ms__echo(char **argv, t_array *env, t_s *s)
{
	int new_line;
	(void)env;
	(void)s;

	if (OK == ft_str_cmp("-n", argv[0]))
	{
		new_line = 0;
		argv += 1;
	}
	else
		new_line = 1;
	if (OK == ft_str_cmp("-", argv[0]))
		argv += 1;
	ft_strsplit_print(argv, ' ');
	if (new_line)
		ft_printf("\n");
	return (OK);
}
