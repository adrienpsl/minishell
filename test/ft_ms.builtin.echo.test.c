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

typedef struct s
{
	int nb_test;
	int nb_line;
	char *argument_str;
	char *result_str;
} t;

static void func_test(t t)
{
	g_test = 1;
	char **argv = ft_strsplit(t.argument_str, " ");
	ms__echo(argv, NULL);

	if (test_cmp_testbuff(t.result_str))
		log_test_line(t.nb_test, t.nb_line)

	ft_strsplit_free(&argv);
	g_test = 0;
}

void test_ms__echo()
{
	// no arguments
	func_test((t){0, L, "", "\n"});

	// -
	func_test((t){1, L, "", "\n"});

	// -n
	func_test((t){2, L, "-n", ""});

	// one argv
	func_test((t){3, L, "toto", "toto\n"});

	// two argument
	func_test((t){3, L, "toto aoue\n", "toto aoue\n\n"});

	// two argument and -
	func_test((t){3, L, "- toto aoue\n", "toto aoue\n\n"});

	// two argument and -n
	func_test((t){3, L, "-n toto aoue\n", "toto aoue\n"});

	// bad option
	func_test((t){3, L, "-naeou toto aoue\n", "-naeou toto aoue\n\n"});

}
