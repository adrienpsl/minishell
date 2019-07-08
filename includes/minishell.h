#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#import "ft_libft.h"

/*
* * ft_errno_set error
*/
enum ms_error
{
	NO_ENV,
	BAD_VAR,
	BAD_DELETING_KEY,
	STR_NOT_IN_PATH,
	OLDPATH_HAS_BE_DELETED,
	HOME_HAS_BE_DELETED,
	INVALID_PATH,
};

typedef struct s_ms
{
	char **env;
	char **arg;
	char **cmd;
	char **path;
	char *home;
	char *debug;
	int test;
	int error;
	char tmp_buffer[4097];
	char testing_str[10000];
	char pwd[4096];
	char *current_err;
} t_ms;

int g_errno;
t_ms ms;

// env
int ms_env_remove(char *removing_var);
int ms_env_copy(char **env);
int ms_env_add(char *new_var);
char *env_get_value(char *key);
int ms_env_modify(char *key, char *new_value);

// builtin
int ms_cd(char **argv);
// echo
// env
//
//

// error
int ft_errno_set(int type_error);

// test
void test_all();

#endif //MINISHELL_MINISHELL_H
