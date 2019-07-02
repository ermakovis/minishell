#include "minishell.h"

void	msh_env(t_msh *msh)
{
	int		i;
	char	**env;

	i = -1;
	env = msh->env;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}
