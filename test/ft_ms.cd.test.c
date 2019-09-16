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

#include <ft_test.h>
#include "libft.h"
# include "../src/cd/ft_ms.cd.c"
void test_init_g_ms(char *str);

typedef struct s
{
	int nb_test;
	int nb_line;

	int size;
	char *env_str;
	char *argv_str;

	int result_int;
	char *result_str;
	char *result_print;
} t;


//void static test_serialize_path(t t)
//{
//	g_test = 1;
//
//	test_init_g_ms(t.env_str);
//	char **argv = ft_strsplit(t.argv_str, " ");
//
//	int ret = cd__serialize_path(argv, g_ms.env, g_ms.buffer_cd);
//
//	if (test_cmp_int(t.result_int, ret))
//		log_test_line(t.nb_test, t.nb_line)
//	if (test_cmp_str(t.result_str, g_ms.buffer_cd->data))
//		log_test_line(t.nb_test, t.nb_line)
//	if (test_cmp_testbuff(t.result_print))
//		log_test_line(t.nb_test, t.nb_line);
//
//	ms__free();
//	ft_strsplit_free(&argv);
//	g_test = 0;
//}


void test_ms__cd()
{
 	/*
 	* test add_start_if_relative
 	* */
	{
		t_s *s = fts__init(10);

		// test with relative path
		fts__add(s, "toto");
		add_start_if_relative(s);
		if (test_cmp_str("/Users/adpusel/code/42/minishell/cmake-build-debug/toto", s->data))
		    log_test(1)

		// test with hard path
		fts__clear(s);
		fts__add(s, "/hey");
		if (test_cmp_str("/hey", s->data))
			log_test(2)


		fts__free(&s);
		
	}
	
}