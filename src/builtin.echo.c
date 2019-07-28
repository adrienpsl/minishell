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

#include "libft.h"

int ms_echo(char **argv)
{
	int end;

	end = 1;
	if (ft_streq(*argv, "-n"))
	{
		end = 0;
		argv++;
	}
	ft_strsplit_print(argv, ' ');
	if (end)
		ft_printf("\n");
	return (0);
}
