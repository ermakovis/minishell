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
	i--;
    ft_memdel((void**)&var);
    return (i);
}

static void	    unset_env(t_msh *msh)
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
        if (!(ft_strnequ(msh->env[i], var, var_len)))
            new[i] = ft_strdup(msh->env[i]);
    }
    clean_table(&(msh->env));
    ft_memdel((void**)&var);
    msh->env = new;
}

void	    msh_unsetenv(t_msh *msh)
{
    char *var;

    if (!msh->tokens[1])
    {
	ft_printf("unsetenv: Too few arguments\n");
	return ;
    }
    if (!(var = ft_strjoin(msh->tokens[1], "=")))
	cleanup(&msh, -1, "Failed to joint strings");
    if (parse_env(var, msh->env))
	unset_env(msh);
    ft_memdel((void**)&var);
}
