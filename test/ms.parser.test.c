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
#include <ft_test.h>
#include "libft.h"

void test_ms__parse_str()
{
	g_test = 1;

	// test with no data
	{
		test_clear_testbuff();
		char *str = "";
		t_array *res = ms__parse_str(str, " ");

		ftarray__func(res, ftarray__func_print_str, NULL);

		if (
			res == NULL ||
			test_cmp_testbuff("\n")
			)
			log_test(0)

		ftarray__free_func(&res, ftarray__free_func_str, NULL);
	}

	// test with 1 data
	{
		test_clear_testbuff();
		char *str = "minhesttresjolie";
		t_array *res = ms__parse_str(str, " ");

		ftarray__func(res, ftarray__func_print_str, NULL);

		if (
			res == NULL ||
			test_cmp_testbuff(" _minhesttresjolie_ \n")
			)
			log_test(0)

		ftarray__free_func(&res, ftarray__free_func_str, NULL);
	}

	// test with 3 element
	{
		test_clear_testbuff();
		char *str = "el_1; el_2 ;el_3";
		t_array *res = ms__parse_str(str, ";");

		ftarray__func(res, ftarray__func_print_str, NULL);

		if (
			res == NULL ||
			test_cmp_testbuff(" _el_1_  _ el_2 _  _el_3_ \n")
			)
			log_test(0)

		ftarray__free_func(&res, ftarray__free_func_str, NULL);
	}

	// test with 1000
	{
		test_clear_testbuff();

		t_s *s = fts__init(100);
		fts__add(s, "el_1; el_2 ;el_3");

		for (int i = 0; i < 1000; ++i)
		{
			fts__add(s, s->data);
		}
		t_array *res = ms__parse_str(s->data, ";");
		char **split = ft_strsplit(s->data, ";");

		if (ft_strsplit_cmp(split, (char **)res->data))
			log_test(10)

		ftarray__free_func(&res, ftarray__free_func_str, NULL);
		ft_strsplit_free(&split);
		fts__free(&s);
	}

	/*
	* test get line
	* */
	{
		// test with one line
		{

		}

	}


	g_test = 0;
}
