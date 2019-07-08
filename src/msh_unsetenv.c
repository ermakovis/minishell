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
	i--;
    ft_memdel((void**)&var);
    return (i);
}

static void	    unset_env()
{
    int	    i;
    char    *var;
    int	    var_len;
    char    **new;
    int	    size;

    i = -1;
    size = calc_realloc_size(g_msh);
    if (!(var = ft_strjoin(g_msh->tokens[1], "=")))
	cleanup(-1, "Failed to joint strings");
    var_len = ft_strlen(var);
    if (!(new = (char**)malloc(sizeof(char*) * (size + 1))))
        cleanup(-1, "Failed to realloc for new env");
    ft_bzero(new, sizeof(char*) * (size + 1));
    while (g_msh->env[++i])
    {
        if (!(ft_strnequ(g_msh->env[i], var, var_len)))
            new[i] = ft_strdup(g_msh->env[i]);
    }
    clean_table(&(g_msh->env));
    ft_memdel((void**)&var);
    g_msh->env = new;
}

void	    msh_unsetenv()
{
    char *var;

    if (!g_msh->tokens[1])
    {
	ft_printf("unsetenv: Too few arguments\n");
	return ;
    }
    if (!(var = ft_strjoin(g_msh->tokens[1], "=")))
	cleanup(-1, "Failed to joint strings");
    if (parse_env(var, g_msh->env))
	unset_env();
    ft_memdel((void**)&var);
}
