#ifndef MINISHELL_TEST_H
#define MINISHELL_TEST_H

typedef struct s_split
{
	char **env;
	char **new_env;
	char **argv;
} t_split;



typedef struct full_test
{
	int nb_test;
	char *env;
	char *new;
	char *argv;
	char *pwd;
	char *print;
	long option;
	int ret_int;
	char *ret_char;
	t_split split;
} ms_test;

#endif //MINISHELL_TEST_H
