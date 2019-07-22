#ifndef MINISHELL_MINISHELL_ERROR_H
#define MINISHELL_MINISHELL_ERROR_H

/*
** Memory **********************************************************************
*/
# define MS_NO_MEMORY "Lack of memory, please buy a new computer! \n"

/*
** Env error *******************************************************************
*/
# define MS_NEW_ENV_TOO_BIG "The env size max is 100\n"

/*
** Setenv error ****************************************************************
*/
# define MS_SETENV_NB_ARGV "Too much argv are given\n"
# define MS_SETENV_SIZE_MAX "SIZE MAX var-name + value == 4095\n"



/*
** Parser size *****************************************************************
*/



/*
** cd builtin ******************************************************************
*/
# define MS_CD_NO_AUTHORIZE "cd: permission denied: %s\n"
# define MS_CD_NO_IN_PWD "cd: string not in pwd: %s\n"

/*
** env builtin *****************************************************************
*/
# define MS_CD_ENV_BAD_OPTION "env: bad option given !\n"
# define MS_CD_ENV_NO_ARGV "env: option requires an argument !\n"


#endif //MINISHELL_MINISHELL_ERROR_H
