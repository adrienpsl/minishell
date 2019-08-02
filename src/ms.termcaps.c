
#include <stdlib.h>
#include <termcap.h>
# include "minishell.h"

int init_termcaps()
{
	static char term_buffer[2048];
	char *termtype = getenv("TERM");

	int success;

	if (termtype == 0)
	{
		ft_put_int(-1,
				   "Specify a terminal type with `setenv TERM <yourtype>'.\n");
	}
	success = tgetent(term_buffer, termtype);
	if (success < 0)
		ft_put_int(-1, "Could not access the termcap data base.\n");
	if (success == 0)
		ft_put_int(-1, "Terminal type is not defined.\n");
	tputs("cl", 1, putchar);
	return (0);
}