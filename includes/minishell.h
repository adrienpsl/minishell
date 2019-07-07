#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#import "ft_libft.h"

/*
* * ft_errno error
*/
enum ms_error
{
	NO_ENV = 2,
	BAD_VAR,
	BAD_DELETING_KEY,
	STR_NOT_IN_PATH,
	OLDPATH_HAS_BE_DELETED,
	HOME_HAS_BE_DELETED
};

typedef struct s_ms
{
	char **p_env;
	char **arg;
	char **cmd;
	char **path;
	char *home;
	char *debug;
	int error;
	char cur_path[4096];
	char pwd[4096];
	char *current_err;
} t_ms;

// env
int ms_env_remove(char *removing_var, t_ms *ms);
int ms_env_copy(char **env, t_ms *ms);
int ms_env_add(char *new_var, t_ms *ms);
char *ms_get_env_value(char *key, char **env);

// builtin
int ms_cd(t_ms *ms);
// echo
// env
//
//

// error
int set_ft_errno(int type_error, char *information, t_ms *ms);

// test
void test_all();

#endif //MINISHELL_MINISHELL_H
