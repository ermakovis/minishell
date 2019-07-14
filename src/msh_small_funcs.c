#include "minishell.h"

void	msh_exit()
{
    set_terminal_canon();
    cleanup(0, NULL);
    exit (1);
}

void	msh_env()
{
    int		i;
    t_list	*env;

    i = -1;
    env = g_msh->env;
    while (env)
    {
	ft_printf("%s\n", env->content);
	env = env->next;
    }
}
