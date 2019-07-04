#include "minishell.h"

void	get_command(t_msh *msh)
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
    while (1)
    {
	ch = ft_getchar();
	if (ch == EOF || ch == '\n')
	{
	    cmd[i] = '\0';
	    msh->command = cmd;
	    return ;
	}
	cmd[i++] = ch;
	if (i == buff_size)
	{
	    buff_size += MSH_BUFF_SIZE;
	    if (!(ft_notrealloc(cmd, i, buff_size))) 
	    {
		ft_memdel((void**)&cmd);
		cleanup(&msh, -1, "Failed to realloc for command");
	    }
	}
    }
}

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
    while (1)
    {
	display_prompt(msh);
	get_command(msh);
	msh->tokens = ft_strsplit(msh->command, ' ');
	launch_program(msh);
	ft_memdel((void**)&msh->command);
	clean_table(&(msh->tokens));
    }
    return (1);
}

