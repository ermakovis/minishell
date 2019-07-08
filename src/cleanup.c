#include "minishell.h"

void	clean_builtins(t_bin **bin)
{
    t_bin   *cur;
    t_bin   *next;

    cur = *bin;
    while (cur)
    {
	next = cur->next;
	ft_memdel((void**)&(cur->name));
	cur->next = NULL;
	cur->func = NULL;
	ft_memdel((void**)&cur);
	cur = next;
    }
    *bin = cur;
}

void	clean_tokens(t_tok **tok)
{
    t_tok   *cur;
    t_tok   *next;

    cur = *tok;
    while (cur)
    {
	next = cur->next;
	ft_memdel((void**)&(cur->token));
	cur->next = NULL;
	ft_memdel((void**)&cur);
	cur = next;
    }
    *tok = cur;
}

void	clean_vars(t_var **var)
{
    t_var	*cur;
    t_var	*next;

    cur = *var;
    while (cur)
    {
	next = cur->next;
	ft_memdel((void**)&(cur->name));
	ft_memdel((void**)&(cur->value));
	cur->next = NULL;
	ft_memdel((void**)&cur);
	cur = next;
    }
    *var = cur;
}

void	clean_table(char ***table)
{
    int	    i;
    char    **tmp;

    if (!*table)
	return ;
    i = -1;
    tmp = *table;
    while(tmp[++i])
	ft_memdel((void**)&tmp[i]);
    ft_memdel((void**)&tmp);
    *table = NULL;
}


void	cleanup(int exit_code, char *message)
{
    if (message)
	ft_dprintf(2, "%s\n", message);
    if (!g_msh)
	exit (exit_code);
    if (g_msh->tok)
	clean_tokens(&(g_msh->tok));
    if (g_msh->env)
	clean_table(&(g_msh->env));
    if (g_msh->tokens)
	clean_table(&(g_msh->tokens));
    if (g_msh->bin)
	clean_builtins(&(g_msh->bin));
    ft_memdel((void**)&g_msh);
    if (exit_code != 1)
	exit (exit_code);
}
