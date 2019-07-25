#ifndef MINISHELL_MINISHELL_ERROR_H
#define MINISHELL_MINISHELL_ERROR_H

/*
** ALL *************************************************************************
*/
# define MS_BAD_NB_ARG "too many arguments"
# define MS_BUFFER_ERROR "MAX SIZE ARGV "

/*
** Memory **********************************************************************
*/
# define MS_NO_MEMORY "Lack of memory, please buy a new computer!"

/*
** Env error *******************************************************************
*/
# define MS_NEW_ENV_TOO_BIG "The env size max is 100"

/*
** Setenv error ****************************************************************
*/
# define MS_SETENV_SIZE_MAX "SIZE MAX var-name + value == 4095"
# define MS_SETENV_FORBIDDEN_CHAR "one = & no $"

/*
** Parser size *****************************************************************
*/

/*
** cd builtin ******************************************************************
*/
# define MS_CD_NO_AUTHORIZE "cd: permission denied: %s"
# define MS_CD_NO_IN_PWD "cd: string not in pwd: %s"
# define MS_CD_NO_HOME "cd: there is no $HOME"
# define MS_CD_NO_OLDPATH "cd: there is no $OLDPATH"

/*
** env builtin *****************************************************************
*/
# define MS_CD_ENV_BAD_OPTION "env: bad option given !"
# define MS_CD_ENV_NO_ARGV "env: option requires an argument !"

#endif //MINISHELL_MINISHELL_ERROR_H
