#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#import "ft_libft.h"
# define NO_ENV -2
# define BAD_VAR -3
# define BAD_DELETING_KEY -4


typedef struct s_ms
{
	char **p_env;
	char **arg;
	char **cmd;
	char **path;
	char *home;
	char *debug;
} t_ms;

// env
int ft_ms_env_remove(char *removing_var, t_ms *ms);
int ft_ms_env_copy(char **env, t_ms *ms);
int ft_ms_env_add(char *new_var, t_ms *ms);


// test
void test_all();

#endif //MINISHELL_MINISHELL_H
