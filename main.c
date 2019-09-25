int ms__init(char **env_system);

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	ms__init(env);
	return (1);
}
