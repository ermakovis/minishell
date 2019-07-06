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
	t_msh   *msh;

	msh = NULL;
	signal(SIGINT, handle_sigint);
	process_env(env, &msh);
	process_builtins(msh);
	display_prompt(msh);
	while (process_tokens(msh))
	{
		launch_program(msh);
		display_prompt(msh);
	}
	cleanup(&msh, 0, NULL);
}

