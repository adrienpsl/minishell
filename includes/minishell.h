#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

extern int g_ft_errno;
int set_ft_errno(int type_error);

#import "ft_libft.h"

# define NO_ENV -2
# define BAD_VAR -3
# define BAD_DELETING_KEY -4
/*
* * ft_errno error
*/
# define PATH_HAS_BE_DELETED -5
# define STR_NOT_IN_PATH -6

typedef struct s_ms
{
	char **p_env;
	char **arg;
	char **cmd;
	char **path;
	char *home;
	char *debug;
	int error;
	char curpath[4096];
	char pwd[4096];
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

// test
void test_all();

#endif //MINISHELL_MINISHELL_H
