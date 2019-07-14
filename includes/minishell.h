#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#import "libft.h"

/*
* * ft_errno_set error
*/
enum ms_error
{
	NO_ENV = 100,
	BAD_VAR,
	BAD_DELETING_KEY,
	STR_NOT_IN_PATH,
	OLDPATH_HAS_BE_DELETED,
	HOME_HAS_BE_DELETED,
	INVALID_PATH,
};

typedef struct s_ms
{
//	int start;
//	int end;
//	char *current;
int i;
	char **env;
	int test;
	char *buffer;
	char **arg;
	char buffer_array[4097];
	char testing_str[10000];
} t_ms;

int g_errno;
int g_fd;
t_ms m;

// env
int ms_env_remove(char *removing_var);
int ms_env_copy(char **env);
int ms_env_add(char **argv);
char *env_get_value(char *key);
int ms_env_modify(char *key, char *new_value);

int is_quote_paired(char *command);
char *get_all_commands();

// parse
char **build_argv(char *line);
char **read_command();

// builtin
int ms_cd(char **argv);
char *get_env_variable(char *line, int end);
char *replace_env_variable(char *line);
// echo
// env
//
//

// error
int ft_errno_set(int type_error);

// test
void test_all();

#endif //MINISHELL_MINISHELL_H
