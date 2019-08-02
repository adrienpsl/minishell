
#include <stdlib.h>
#include <termcap.h>
# include "minishell.h"

static char term_buffer[2048];

int init_termcaps()
{

	// It seem that I can't use the catch termcaps with zsh and iterm
	// may be with bash?
	// I get the name / type of terminal to look up
	char *termtype = getenv("TERM");

	int success;

	if (termtype == 0)
		printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");

	// I use the terminal type to init the lib and remember what I
	// can do with it.
	success = tgetent(term_buffer, termtype);
	if (success < 0)
		printf("Could not access the termcap data base.\n");
	if (success == 0)
		printf("Terminal type `%s' is not defined.\n", termtype);
	tputs("cl", 1, putchar);

	return (0);
}