#include "minishell.h"

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		return ;
	}
}

int	main(int argc, char **argv, char **env)
{
	signal(SIGINT, handle_sigint);
	process_env(env);
	process_builtins();
	display_prompt();
	while (process_tokens())
	{
		launch_program();
		display_prompt();
	}
	cleanup(0, NULL);
}

