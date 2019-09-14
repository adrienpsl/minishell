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

void test_ms__parse_env();
void test_ms__parse_str();
void test_ms__find_binary();
void test_ms__get_line();
void test_ms__env();

void test_all()
{
	//	test_ms__parse_env();
	//	test_ms__parse_str();
	//	test_ms__find_binary();
	//	test_ms__get_line();
	test_ms__env();
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	test_all();
	return (EXIT_SUCCESS);
}