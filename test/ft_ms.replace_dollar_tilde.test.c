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

#include <minishell.h>

struct test
{
	int line_nb;

	char *env_str;
	char *argv_str;
	char *path_str;

	char *expect_print;
	char *expect_char;
	int expect_int;
};

int replace_dollar_tilde(
	const char **env,
	const char *const line,
	char **p_new_line);

void t_replace_dollar_tilde(struct test t)
{
	g_test = 1;
	const char **env = (void *)ft_strsplit(t.env_str, " ");

	char *new_line = ft_strdup(t.argv_str);
	int ret = replace_dollar_tilde(env, new_line, &new_line);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_str(t.expect_char, new_line))
		log_test_line(1, t.line_nb)

	ft_strsplit_free((char ***)&env);
}

void test_replace_dollar_tilde()
{
	//	t_replace_dollar_tilde((struct test){ .line_nb  = L,
	//		.env_str = "",
	//		.argv_str = "",
	//
	//		.expect_int = OK,
	//		.expect_char = ""
	//	});
	//
	//	t_replace_dollar_tilde((struct test){ .line_nb  = L,
	//		.env_str = "",
	//		.argv_str = "toto",
	//
	//		.expect_int = OK,
	//		.expect_char = "toto"
	//	});
	//
	//	t_replace_dollar_tilde((struct test){ .line_nb  = L,
	//		.env_str = "",
	//		.argv_str = "toto$",
	//
	//		.expect_int = OK,
	//		.expect_char = "toto$"
	//	});

	t_replace_dollar_tilde((struct test){ .line_nb  = L,
		.env_str = "",
		.argv_str = "$toto",

		.expect_int = OK,
		.expect_char = ""
	});
}