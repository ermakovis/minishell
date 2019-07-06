#include "minishell.h"

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		return ;
	}
}

int		get_command(t_msh *msh)
{
	int	    i;
	int	    buff_size;
	int	    ch;
	char    *cmd;

	i = 0;
	buff_size = MSH_BUFF_SIZE;
	if (!(cmd = (char*)malloc(MSH_BUFF_SIZE)))
		cleanup(&msh, -1, "Failed to malloc for command");
	ft_bzero(cmd, MSH_BUFF_SIZE);
	while ((ch = ft_getchar()) >= 0)
	{
		if (ch == 0 || ch == '\n')
		{
			msh->command = cmd;
			return (1);
		}
		cmd[i++] = ch;
		if (i == buff_size)
		{
			buff_size += MSH_BUFF_SIZE;
			if (!(cmd = ft_notrealloc(cmd, i, buff_size))) 
			{
				ft_memdel((void**)&cmd);
				cleanup(&msh, -1, "Failed to realloc for command");
			}
		}
	}
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	t_msh   *msh;

	msh = NULL;
	signal(SIGINT, handle_sigint);
	process_env(env, &msh);
	process_builtins(msh);
	display_prompt(msh);
	process_tokens(msh);
	while (tok)
	{
		ft_printf("%s\n", tok->token);
		tok = tok->next;
	}
//	while (get_command(msh))
//	{
//		get_tokens(msh);
//		msh->tokens = ft_strsplit(msh->command, ' ');
//		launch_program(msh);
//		ft_memdel((void**)&msh->command);
//		clean_table(&(msh->tokens));
//		display_prompt(msh);
//	}
//	cleanup(&msh, 0, NULL);
}

