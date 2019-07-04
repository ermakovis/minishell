#include "minishell.h"

static int	    calc_realloc_size(t_msh *msh)
{
    int	    i;
    char    *var;

    i = 0;
    while (msh->env[i])
	i++;
    if (!(var = ft_strjoin(msh->tokens[1], "=")))
	cleanup(&msh, -1, "Failed to joint strings");
    if (!(parse_env(var, msh->env)))
	i++;
    ft_memdel((void**)&var);
    return (i);
}

static void	    set_env(t_msh *msh)
{
    int	    i;
    char    *var;
    int	    var_len;
    char    **new;
    int	    size;

    i = -1;
    size = calc_realloc_size(msh);
    if (!(var = ft_strjoin(msh->tokens[1], "=")))
	cleanup(&msh, -1, "Failed to joint strings");
    var_len = ft_strlen(var);
    if (!(new = (char**)malloc(sizeof(char*) * (size + 1))))
        cleanup(&msh, -1, "Failed to realloc for new env");
    ft_bzero(new, sizeof(char*) * (size + 1));
    while (msh->env[++i])
    {
        if (ft_strnequ(msh->env[i], var, var_len))
            new[i] = ft_strjoin(var, msh->tokens[2]);
        else
            new[i] = ft_strdup(msh->env[i]);
    }
    if (i < size)
        new[i] = ft_strjoin(var, msh->tokens[2]);
    clean_table(&(msh->env));
    ft_memdel((void**)&var);
    msh->env = new;
}

#include <stdio.h>

void	    msh_setenv(t_msh *msh)
{
    int	    tokens_count;

    tokens_count = ft_tablesize(msh->tokens);
    if (tokens_count == 1)
	msh_env(msh);
    else if (tokens_count > 3)
    {
	ft_printf("setenv: Too many arguments.\n");
    }
    else
	set_env(msh);
}
