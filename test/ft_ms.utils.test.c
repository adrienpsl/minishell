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

#include <libft.h>
#include <ft_test.h>
#include <minishell.prototypes.h>
#include  "../src/ft_ms.utils_1.c"

void test_ms__utils()
{
	/*
	* test ms__get_value
	* */
	{
		char **env;
		char *response;
		env = ft_strsplit("val1=toto =error val2=titi val3=tata val4=tito",
			" ");

		// value not exist
		response = ms__get_value(env, "val30");
		if (test_cmp_str(NULL, response))
			log_test(0)
		ftstr__free(&response);

		// start
		response = ms__get_value(env, "val1");
		if (test_cmp_str("toto", response))
			log_test(1)
		ftstr__free(&response);

		// start
		response = ms__get_value(env, "val4");
		if (test_cmp_str("tito", response))
			log_test(1)
		ftstr__free(&response);

		// value does not exist
		ft_strsplit_free(&env);
	}

	/*
	* test ms__env_delete
	* */
	{
		g_test = 1;
		char **env;
		env = ft_strsplit("val1=toto =error val2=titi val3=tata val4=tito",
			" ");


		// delete no exist
		ms__env_delete(env, "toto");
		ft_strsplit_print(env, ' ');

		if (test_cmp_buff("val1=toto =error val2=titi val3=tata val4=tito"))
			log_test(1)

		// delete exist
		ms__env_delete(env, "val2");
		ft_strsplit_print(env, ' ');

		if (test_cmp_buff("val1=toto =error val3=tata val4=tito"))
			log_test(1)

		ft_strsplit_free(&env);
		g_test = 0;
	}

	/*
	* test ms__env_add
	* */
	{
		g_test = 1;
		char **env = ft_strsplit(
			"val1=toto =error val2=titi val3=tata val4=tito", " ");

		// new
		ms__env_add(&env, "minh", "tresJolie");
		ft_strsplit_print(env, ' ');

		if (test_cmp_buff("val1=toto =error val2=titi val3=tata val4=tito minh=tresJolie"))
			log_test(1)

		// existing
		ms__env_add(&env, "val2", "tresJolie");
		ft_strsplit_print(env, ' ');

		if (test_cmp_buff("val1=toto =error val3=tata val4=tito minh=tresJolie val2=tresJolie"))
			log_test(1)


		ft_strsplit_free(&env);
		g_test = 0;
	}
}
