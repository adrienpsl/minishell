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
#include  "../src/ft_ms.env.utils.c"

struct test
{
	int line_nb;

	char *env_str;
	char *line_str;

	char *expect_line;
};

void t_replace_dollar(struct test t)
{
	g_test = 1;
	char **env = ft_strsplit(t.env_str, " ");
	//	char *fresh_line = ft_strdup(t.line_str);

	//	char *result_char = replace_dollar(fresh_line, env);

	//	if (test_cmp_str(t.expect_line, result_char))
	//		log_test_line(1, t.line_nb)

	ft_strsplit_free(&env);
	//	free(result_char);
}

void test_replace_dollar()
{
	// all empty
	t_replace_dollar((struct test){ .line_nb = L,
		.env_str = "",
		.line_str = "",

		.expect_line = ""
	});

	// no $
	t_replace_dollar((struct test){ .line_nb = L,
		.env_str = "",
		.line_str = "toto",
		.expect_line = "toto"
	});

	// no test $
	t_replace_dollar((struct test){ .line_nb = L,
		.env_str = "",
		.line_str = "$ toto",
		.expect_line = "$ toto"
	});

	// no test $ at the end
	t_replace_dollar((struct test){ .line_nb = L,
		.env_str = "",
		.line_str = "toto$",
		.expect_line = "toto$"
	});

	// no test $ at the end
	t_replace_dollar((struct test){ .line_nb = L,
		.env_str = "",
		.line_str = "toto$",
		.expect_line = "toto$"
	});

	t_replace_dollar((struct test){ .line_nb = L,
		.env_str = "toto=test",
		.line_str = "$toto",
		.expect_line = "test"
	});

	t_replace_dollar((struct test){ .line_nb = L,
		.env_str = "toto=test",
		.line_str = "$toto $toto",
		.expect_line = "test test"
	});
}



void test_ms__utils()
{
	test_replace_dollar();

	/*
	* test ms__get_value
	* */
	{
		char **env;
		char *response;
		env = ft_strsplit("val1=toto =error val2=titi val3=tata val4=tito",
			" ");

		// value not exist
		response = ms__env_get_value(env, "val30");
		if (test_cmp_str(NULL, response))
			log_test(0)
		ftstr__free(&response);

		// start
		response = ms__env_get_value(env, "val1");
		if (test_cmp_str("toto", response))
			log_test(1)

		// start
		response = ms__env_get_value(env, "val4");
		if (test_cmp_str("tito", response))
			log_test(1)

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
}

