#include "minishell.h"

void	cleanup(int exit_code, char *message)
{
    if (message)
	ft_dprintf(2, "%s\n", message);
    if (!g_msh)
	exit (exit_code);
    ft_lstdel(&(g_msh->env), &delete_str);
    ft_lstdel(&(g_msh->bin), &delete_builtins);
    ft_memdel((void**)&g_msh);
    if (exit_code != 1)
	exit (exit_code);
}
