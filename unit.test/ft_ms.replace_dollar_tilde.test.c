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
	char *line;

	char *expect_print;
	char *expect_new_line;
	int expect_int;
	char *expect_line;
};

void t_replace_dollar(struct test t)
{
	g_test = 1;
	char **env = (void *)ft_strsplit(t.env_str, " ");
	char *new_line = ft_strdup("");
	char *line = t.line;

	ms_replace_dollar(&line, &new_line, env);

	if (test_cmp_str(t.expect_new_line, new_line)
		|| test_cmp_str(t.expect_line, line))
		log_test_line(1, t.line_nb)

	ft_strsplit_free((char ***)&env);
	ftstr__free(&new_line);
}

void t_replace_dollar_tilde(struct test t)
{
	g_test = 1;
	const char **env = (void *)ft_strsplit(t.env_str, " ");

	char *new_line = NULL;
	int ret = replace_dollar_tilde(env, t.line, &new_line);

	if (test_cmp_int(t.expect_int, ret)
		|| test_cmp_str(t.expect_new_line, new_line))
		log_test_line(1, t.line_nb)

	ft_strsplit_free((char ***)&env);
	ftstr__free(&new_line);
}

void test_replace_dollar_tilde()
{
	/*
	* replace dollar
	* */
	{
		//		no data
		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "",
			.line = "",

			.expect_new_line = "",
			.expect_line = ""
		});

		// noting to replace
		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "toto=titi",
			.line = "toto",

			.expect_new_line = "",
			.expect_line = "toto"
		});

		// bad $
		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "toto=titi",
			.line = "toto$",

			.expect_new_line = "",
			.expect_line = "toto$"
		});

		// bad $
		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "toto=titi",
			.line = "toto$$$",

			.expect_new_line = "",
			.expect_line = "toto$$$"
		});

		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "toto=titi",
			.line = "toto$ ",

			.expect_new_line = "",
			.expect_line = "toto$ "
		});

		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "toto=titi",
			.line = "toto$/ aoeu ",

			.expect_new_line = "",
			.expect_line = "toto$/ aoeu "
		});

		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "tot=titi",
			.line = "$toto",

			.expect_new_line = "",
			.expect_line = ""
		});

		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "tototiti",
			.line = "$toto/",

			.expect_new_line = "",
			.expect_line = "/"
		});

		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "toto=titi",
			.line = "$toto",

			.expect_new_line = "titi",
			.expect_line = ""
		});

		t_replace_dollar((struct test){ .line_nb  = L,
			.env_str = "toto=titi tata=tutu",
			.line = "$toto$tata end",

			.expect_new_line = "titi",
			.expect_line = "$tata end"
		});
	}

	/*
	* replace dollar and tilde
	* */
	{
		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "",
			.line = "",

			.expect_new_line = "",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "",
			.line = "toto",

			.expect_new_line = "toto",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "",
			.line = "toto",
			.expect_new_line = "toto",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "",
			.line = "toto$",
			.expect_new_line = "toto$",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "",
			.line = "toto$toto",
			.expect_new_line = "toto",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "",
			.line = "toto$~",
			.expect_new_line = "toto$",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "HOME=super",
			.line = "toto$~",
			.expect_new_line = "toto$super",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "HOME=super heytoto hey=super",
			.line = "toto$~$hey",
			.expect_new_line = "toto$supersuper",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "HOME=super heytoto hey=super",
			.line = "toto$~$hey $hey/ oups",
			.expect_new_line = "toto$supersuper super/ oups",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "HOME=super heytoto hey=super",
			.line = "toto$~$hey $hey/ oups$nononono$ooo",
			.expect_new_line = "toto$supersuper super/ oups",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "HOME=super heytoto hey=super",
			.line = "$",
			.expect_new_line = "$",
		});

		t_replace_dollar_tilde((struct test){ .line_nb  = L,
			.env_str = "HOME=super heytoto hey=super",
			.line = "~",
			.expect_new_line = "super",
		});
	}
}