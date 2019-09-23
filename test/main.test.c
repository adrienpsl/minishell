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
#include "libft.h"

void test_ms__utils();
void test__main_cd();
void test_main_env();
void test_utils_env();
void test__execve();

void test_all()
{
	test_ms__utils();
	test__main_cd();
	test_main_env();
	test_utils_env();
//	test__execve();
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	test_all();
	return (EXIT_SUCCESS);
}
