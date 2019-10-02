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

#ifndef FT_TEST_H
# define FT_TEST_H

# include "stdio.h"
# include "my_test.h"

extern int		g_test;
int				g_test;
extern char		g_test_buffer[100000];
char			g_test_buffer[100000];

int				test_random_int(int limit);
void			test_print_func_int(void *ptr);

void			test_clear_testbuff(void);
int				test_cmp_testbuff_log(char *expected);
int				test_cmp_buff(char *expected);

int				test_cmp_str(char *result, char *ret);
int				test_cmp_split_str(char *name, char *expected, char **returned);
int				test_cmp_int(int expected, int returned);

#endif
