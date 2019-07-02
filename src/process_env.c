#include "minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	i = -1;
	while(env[++i]);
	if (!(new_env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
	}
	new_env[i] = NULL;
	return (new_env);
}

int	    process_env(char **env, t_msh **msh)
{
	t_msh	*new_msh;
    int	    i = -1;

	if (!(new_msh = malloc(sizeof(t_msh))))
		return (0);
    ft_bzero(new_msh, sizeof(t_msh));
    new_msh->env = copy_env(env);
	*msh = new_msh;
    return (1);
}
