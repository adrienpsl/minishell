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

	/*
	* bad entry
	* */
	{
		// test with no env data
		{
			t_array *env;
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
			t_array *env = ms__parse_env(char_env);

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
			t_array *env = ms__parse_env(char_env);

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
			t_array *env = ms__parse_env(char_env);

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
			t_array *env = ms__parse_env(char_env);

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
			t_array *env = ms__parse_env(char_env);

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
			t_array *env = ms__parse_env(char_env);

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

			t_array *env = ms__parse_env((char **)test_array->data);

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
	* test ms_convert_env
	* */
	{
		// test 0
		{
			t_array *test_array = ftarray__init(1000, sizeof(char **));
			char **converted_env;
			t_s *s = fts__init(200);

			t_array *env = ms__parse_env((char **)test_array->data);
			converted_env = ms__convert_env(env, s);

			if (ft_strsplit_cmp(converted_env, (char **)test_array->data))
				log_test(10)

			ft_strsplit_free(&converted_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
			ftarray__free(&test_array);
			fts__free(&s);
		}


		// test 1
		{
			t_array *test_array = ftarray__init(1000, sizeof(char **));
			char *str = "minhesttresjolie=minhesttrestresjolie";
			char **converted_env;
			t_s *s = fts__init(200);

			ftarray__push(test_array, &str);

			t_array *env = ms__parse_env((char **)test_array->data);
			converted_env = ms__convert_env(env, s);

			if (ft_strsplit_cmp(converted_env, (char **)test_array->data))
				log_test(10)

			ft_strsplit_free(&converted_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
			ftarray__free(&test_array);
			fts__free(&s);
		}



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

			t_array *env = ms__parse_env((char **)test_array->data);
			converted_env = ms__convert_env(env, s);

			if (ft_strsplit_cmp(converted_env, (char **)test_array->data))
				log_test(10)

			ft_strsplit_free(&converted_env);
			ftarray__free_func(&env, ms__func_free_env, NULL);
			ftarray__free(&test_array);
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
			t_array *env = ms__parse_env(split);
			t_s *s = fts__init(200);
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


	/*
	* test ms__remove_env
	* */
	{
		int ret;

		// test no variables
		{
			char **split = ft_strsplit("", " ");
			t_array *env = ms__parse_env(split);

			ret = ms__env_remove(env, "minh");

			if (
				ret != -1
				)
				log_test(14)

			ft_strsplit_free(&split);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}

		// test delete one var
		{
			lib_clear_testbuff();
			char **split = ft_strsplit("minh=belle", " ");
			t_array *env = ms__parse_env(split);

			ret = ms__env_remove(env, "minh");
			ftarray__func(env, ms__print_env, NULL);

			if (
				ret != 0 ||
				lib_cmp_testbuff("")
				)
				log_test(15)

			ft_strsplit_free(&split);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}


		// test delete 1 / 2
		{
			lib_clear_testbuff();
			char **split = ft_strsplit("minh=belle super=minh", " ");
			t_array *env = ms__parse_env(split);

			ret = ms__env_remove(env, "minh");
			ftarray__func(env, ms__print_env, NULL);

			if (
				ret != 0 ||
				lib_cmp_testbuff("super=minh\n")
				)
				log_test(15)

			ft_strsplit_free(&split);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}

		// test delete 1 / 3
		{
			lib_clear_testbuff();
			char **split = ft_strsplit("minh=belle super=minh titi=toto", " ");
			t_array *env = ms__parse_env(split);

			ret = ms__env_remove(env, "super");
			ftarray__func(env, ms__print_env, NULL);

			if (
				ret != 0 ||
				lib_cmp_testbuff("minh=belle\ntiti=toto\n")
				)
				log_test(15)

			ft_strsplit_free(&split);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}

		// test delete 1 / 3 no element
		{
			lib_clear_testbuff();
			char **split = ft_strsplit("minh=belle super=minh titi=toto", " ");
			t_array *env = ms__parse_env(split);

			ret = ms__env_remove(env, "su");
			ftarray__func(env, ms__print_env, NULL);

			if (
				ret != -1 ||
				lib_cmp_testbuff("minh=belle\nsuper=minh\ntiti=toto\n")
				)
				log_test(15)

			ft_strsplit_free(&split);
			ftarray__free_func(&env, ms__func_free_env, NULL);
		}
	}


	/*
	* test ms_add_env
	* */
	{
		// bad entry
		{
			// test add variable no valid
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit("", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, NULL, NULL, "minhestbell");
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != -1 ||
					lib_cmp_testbuff(
						"minishell: setenv wrong variables: [ minhestbell ]\n")
					)
					log_test(16)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}

			// test null key
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit("", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, "", "toto", NULL);
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != -1 ||
					lib_cmp_testbuff(
						"minishell: setenv wrong variables [  ]  [ toto ]\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}

			// test null value
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit("", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, "toto", "", NULL);
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != -1 ||
					lib_cmp_testbuff(
						"minishell: setenv wrong variables [ toto ]  [  ]\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}

			// test key with env
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit("minh=belle", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, "toto", "", NULL);
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != -1 ||
					lib_cmp_testbuff(
						"minishell: setenv wrong variables [ toto ]  [  ]\n"
						"minh=belle\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}

			// test variable null with env
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit("minh=belle", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, "toto", "", "");
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != -1 ||
					lib_cmp_testbuff("minishell: setenv wrong variables: [  ]\n"
									 "minh=belle\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}
		}

		/*
		* ms__env_add good entries
		* */
		{
			// test key / value, new var
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit("minh=belle", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, "toto", "less_beau_minh", NULL);
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != 0 ||
					lib_cmp_testbuff("minh=belle\n"
									 "toto=less_beau_minh\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}

			// test key / value, replace env
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit(
					"minh=belle toto=very_pretty titi=tata", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, "toto", "less_beau_minh", NULL);
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != 0 ||
					lib_cmp_testbuff("minh=belle\n"
									 "titi=tata\n"
									 "toto=less_beau_minh\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}

			// test variable, new
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit("minh=belle", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, "", "", "toto=less_beau_minh");
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != 0 ||
					lib_cmp_testbuff("minh=belle\n"
									 "toto=less_beau_minh\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}

			// test variable null with env, variable same key existant
			{
				lib_clear_testbuff();
				int ret;
				char **split = ft_strsplit(
					"minh=belle toto=very_pretty titi=tata", " ");
				t_array *env = ms__parse_env(split);

				ret = ms__env_add(env, NULL, NULL, "toto=less_beau_minh");
				ftarray__func(env, ms__print_env, NULL);

				if (
					ret != 0 ||
					lib_cmp_testbuff("minh=belle\n"
									 "titi=tata\n"
									 "toto=less_beau_minh\n")
					)
					log_test(17)

				ft_strsplit_free(&split);
				ftarray__free_func(&env, ms__func_free_env, NULL);
			}
		}
	}

	g_test = 0;
}