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

#include <ft_array.h>
#include <ft_strsplit.h>
#include <ft_s.h>
#include <ft_printf.h>
#include <libft.test.h>
#include <test.h>
#include <minishell.stuctures.h>
#include <ft_str.h>
#include "minishell.prototypes.h"

char **ms__convert_env(t_array *env, t_s *s);
t_array *ms__parse_env(char **env_system);

int print_string(void *element, void *param)
{
	(void)param;

	ft_printf("%s", *(char **)element);
	return (0);
}

int print_env_element(void *element, void *param)
{
	(void)param;
	t_env_el *el;

	el = element;
	ft_printf("%s=%s", el->key, el->value);
	return (0);
}

void test_ms__parse_env()
{
	g_test = 1;
	lib_clear_testbuff();
	char **char_env;
	(void)char_env;
	t_array *env;
	(void)env;

	/*
	* bad entry
	* */
	{
		// test with no env data
		{
			char_env = ft_strsplit("", " ");
			env = ms__parse_env(char_env);

			ftarray__func(env, print_string, NULL);
			if (
				lib_cmp_testbuff("")
				)
				log_test(0)

			ft_strsplit_free(&char_env);
			ftarray__free(&env);
		}

		// test with no =
		{
			char_env = ft_strsplit("super", " ");
			env = ms__parse_env(char_env);

			ftarray__func(env, print_string, NULL);
			if (
				lib_cmp_testbuff(
					"Env add bad arguments: super\n")
				)
				log_test(1)

			ft_strsplit_free(&char_env);
			ftarray__free(&env);
		}

		// test no value after =
		{
			char_env = ft_strsplit("super=", " ");
			env = ms__parse_env(char_env);

			ftarray__func(env, print_string, NULL);
			if (
				lib_cmp_testbuff(
					"Env add bad arguments: super=\n")
				)
				log_test(2)

			ft_strsplit_free(&char_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}

		// test only =
		{
			char_env = ft_strsplit("=", " ");
			env = ms__parse_env(char_env);

			ftarray__func(env, print_string, NULL);
			if (
				lib_cmp_testbuff(
					"Env add bad arguments: =\n")
				)
				log_test(3)

			ft_strsplit_free(&char_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}

		// test only = and stuff
		{
			char_env = ft_strsplit("======aoeuaoeu", " ");
			env = ms__parse_env(char_env);

			ftarray__func(env, print_string, NULL);
			if (
				lib_cmp_testbuff(
					"Env add bad arguments: ======aoeuaoeu\n")
				)
				log_test(4)

			ft_strsplit_free(&char_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}
	}

	/*
	* Good entry
	* */
	{
		// test one
		{
			char_env = ft_strsplit("super=minh", " ");
			env = ms__parse_env(char_env);

			ftarray__func(env, print_env_element, NULL);
			if (
				lib_cmp_testbuff(
					"super=minh")
				)
				log_test(1)

			ft_strsplit_free(&char_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}

		// test two
		{
			char_env = ft_strsplit(
				"super==miaoeuaoeu,aoeuaeosu,saoeuhaoehusaoehunh toto========aa",
				" ");
			env = ms__parse_env(char_env);

			ftarray__func(env, print_env_element, NULL);
			if (
				lib_cmp_testbuff(
					"super==miaoeuaoeu,aoeuaeosu,saoeuhaoehusaoehunh"
					"toto========aa")
				)
				log_test(1)

			ft_strsplit_free(&char_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}

		// test 1000
		{
			t_array *test_array = ftarray__init(1000, sizeof(char **));
			t_env_el *el;
			int y = 0;
			char *str = "minhesttresjolie=minhesttrestresjolie";
			char *key = "minhesttresjolie";
			char *value = "minhesttrestresjolie";

			for (int i = 0; i < 1000; ++i)
			{
				ftarray__push(test_array, &str);
			}

			env = ms__parse_env((char **)test_array->data);

			while (
				(el = ftarray__next(env))
				)
			{
				if (
					ft_str_cmp(el->key, key)
					|| ft_str_cmp(el->value, value)
					)
					log_test(8)
				y += 1;
			}
			if (y != 1000)
				log_test(9);

			ft_strsplit_free(&char_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}
	}

	/*
	* test mes_convert_env
	* */
	{
		// test 1000
		{
			t_array *test_array = ftarray__init(1000, sizeof(char **));
			char *str = "minhesttresjolie=minhesttrestresjolie";
			char **converted_env;
			t_s *s = fts__init(200);

			for (int i = 0; i < 1000; ++i)
			{
				ftarray__push(test_array, &str);
			}

			env = ms__parse_env((char **)test_array->data);
			converted_env = ms__convert_env(env, s);

			ft_strsplit_print(converted_env, '\n');
			if (ft_strsplit_cmp(converted_env, (char **)test_array->data))
				log_test(10)

			ft_strsplit_free(&converted_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
			fts__free(&s);
		}
	}


	/*
	* test ms_find_env_key
	* */
	{

		// find existing key
		{
			char *str = "minh=jolie Minh=belle MMinh==super=belle";
			char **split = ft_strsplit(str, " ");
			env = ms__parse_env(split);
			t_s *s = fts__init(200);
			(void)s;
			char *res;

			// first
			{
				res = ms__find_env_key(env, "minh");
				if (
					ft_str_cmp(res, "jolie")
					)
					log_test(11)
			}

			// second
			{
				res = ms__find_env_key(env, "Minh");
				if (
					ft_str_cmp(res, "belle")
					)
					log_test(12)
			}

			// third
			{
				res = ms__find_env_key(env, "MMinh");
				if (
					ft_str_cmp(res, "=super=belle")
					)
					log_test(12)
			}

			// no key
			{
				res = ms__find_env_key(env, "MMinhM");
				if (
					ft_str_cmp(res, "")
					)
					log_test(13)
			}

			ft_strsplit_free(&split);
			ftarray__free_func(&env, ms__func_free_env, NULL);
			fts__free(&s);
		}
	}



	g_test = 0;
}