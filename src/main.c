#include <stdio.h>
#include <minishell.h>

void new_test_all();

void ms_activate_raw_mode()
{
	struct termios termios;

	if (!g_ms.is_raw)
	{
		tcgetattr(STDIN_FILENO, &termios);
		tcgetattr(STDIN_FILENO, &g_ms.termios);
		termios.c_lflag &= ~(ICANON | ECHO);
		termios.c_cc[VMIN] = 1;
		termios.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	}
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	if (env == NULL)
		return (EXIT_FAILURE);
	ft_bzero(&g_ms, sizeof(t_ms));
	*ms_get_ptr_env() = ft_strsplit_copy(env, 0);

	//	g_ms.is_test = 1;
	//	new_test_all();
	signal(SIGINT, ms_signal_minishell);
	if (!g_ms.is_test)
		ms_activate_raw_mode();
	ms_command_loop();

	return (0);
}