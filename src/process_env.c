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
		if (!(new_env[i] = ft_strdup(env[i])))
			clean_table(&new_env);
	}
	new_env[i] = NULL;
	return (new_env);
}

void	    process_env(char **env)
{
	t_msh	    *new_msh;
	int	    i = -1;

	if (!(new_msh = malloc(sizeof(t_msh))))
		return ;
	ft_bzero(new_msh, sizeof(t_msh));
	new_msh->env = copy_env(env);
	g_msh = new_msh;
}
