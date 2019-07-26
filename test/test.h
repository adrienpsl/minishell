#ifndef MINISHELL_TEST_H
#define MINISHELL_TEST_H

typedef struct s_split
{
	char **env;
	char **new_env;
	char **argv;
	char **env_tmp;
	char **argv_end;
} t_split;

typedef struct full_test
{
	int nb_test;
	char *env;
	char *new_env;
	char *argv;
	char *pwd;
	char *print;
	long option;
	int ret_int;
	char *ret_char;
	char *env_tmp;
	char *argv_end;

	char *start_repository;
	char *end_repository;
	char *line;

	char *binary_name;
	char *binary_path;

} ms_test;

#endif //MINISHELL_TEST_H
