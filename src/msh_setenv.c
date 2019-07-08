#include "minishell.h"

static int	    calc_realloc_size()
{
    int	    i;
    char    *var;

    i = 0;
    while (g_msh->env[i])
	i++;
    if (!(var = ft_strjoin(g_msh->tokens[1], "=")))
	cleanup(-1, "Failed to joint strings");
    if (!(parse_env(var, g_msh->env)))
	i++;
    ft_memdel((void**)&var);
    return (i);
}

static void	    set_env()
{
    int	    i;
    char    *var;
    int	    var_len;
    char    **new;
    int	    size;

    i = -1;
    size = calc_realloc_size();
    if (!(var = ft_strjoin(g_msh->tokens[1], "=")))
	cleanup(-1, "Failed to joint strings");
    var_len = ft_strlen(var);
    if (!(new = (char**)malloc(sizeof(char*) * (size + 1))))
        cleanup(-1, "Failed to realloc for new env");
    ft_bzero(new, sizeof(char*) * (size + 1));
    while (g_msh->env[++i])
    {
        if (ft_strnequ(g_msh->env[i], var, var_len))
            new[i] = ft_strjoin(var, g_msh->tokens[2]);
        else
            new[i] = ft_strdup(g_msh->env[i]);
    }
    if (i < size)
        new[i] = ft_strjoin(var, g_msh->tokens[2]);
    clean_table(&(g_msh->env));
    ft_memdel((void**)&var);
    g_msh->env = new;
}

#include <stdio.h>

void	    msh_setenv()
{
    int	    tokens_count;

    tokens_count = ft_tablesize(g_msh->tokens);
    if (tokens_count == 1)
	msh_env();
    else if (tokens_count > 3)
    {
	ft_printf("setenv: Too many arguments.\n");
    }
    else
	set_env();
}
