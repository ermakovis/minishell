#include "minishell.h"

static char **process_path(char **env)
{
    int	    i;
    char    **path;

    i = -1;
    path = NULL;
    while (env[++i])
    {
	if (ft_strnequ("PATH=", env[i], 5))
	    if (!(path = ft_strsplit(env[i] + 5, ':')))
		return (NULL);
    }
    return (path);
}

static char *process_cwd(void)
{
    char    cwd[PATH_MAX];
    char    *output;

    ft_bzero(cwd, PATH_MAX);
    output = NULL;
    getcwd(cwd, PATH_MAX);
    if (!(output = ft_strdup(cwd)))
	return (NULL);
    return (output);
}



int	    process_env(char **env, t_msh *msh)
{
    int	    i = -1;

    ft_bzero(msh, sizeof(t_msh));
    ft_memdel((void**)&(msh->env_path));
    msh->env_path = process_path(env); 
    msh->env_cwd = process_cwd();
    return (1);
}
