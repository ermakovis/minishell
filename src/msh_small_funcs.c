#include "minishell.h"

void	    msh_setenv()
{
    char    **tokens;
    int	    tokens_count;

    tokens = g_msh->lch->tokens;
    tokens_count = ft_table_size(tokens);
    if (tokens_count == 1)
	msh_env();
    else if (tokens_count > 3)
	ft_dprintf(2, "setenv: Too many arguments.\n");
    else if (find_var(g_msh->env, tokens[1]))
	set_var(g_msh->env, tokens[1], tokens[2]);
    else
	add_var(tokens[1], tokens[2], &(g_msh->env));
}

void	msh_unsetenv(void)
{
    char    **tokens;
    size_t  tokens_count;

    tokens = g_msh->lch->tokens;
    tokens_count = ft_table_size(tokens);
    if (tokens_count == 1)
	ft_dprintf(2, "unsetenv: Not enough arguments.\n");
    else if (tokens_count > 2)
	ft_dprintf(2, "unsetenv: Too many arguments.\n");
    else
	ft_lst_remove_if(&(g_msh->env), tokens[1], &cmp_var, &delete_var);
}

void	msh_exit()
{
    set_terminal_canon();
    cleanup(0, NULL);
    exit (1);
}

void	msh_env()
{
    ft_lstiter(g_msh->env, &print_var);
}
