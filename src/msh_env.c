#include "minishell.h"

void	msh_env()
{
	int		i;
	char	**env;

	i = -1;
	env = g_msh->env;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}
