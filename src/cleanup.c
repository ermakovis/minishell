#include "minishell.h"

void	clean_table(char ***table)
{
	int	    i;
	char    **tmp;

	i = -1;
	tmp = *table;
	while(tmp[++i])
		ft_memdel((void**)&tmp[i]);
	ft_memdel((void**)&tmp);
	*table = NULL;
}

void	cleanup(t_msh **msh, int exit_code, char *message)
{
	if (message)
		ft_dprintf(2, "%s\n", message);
	if (!msh || !*msh)
		exit (exit_code);
	if ((*msh)->tokens)
		clean_table(&((*msh)->tokens));
	if ((*msh)->env)
		clean_table(&((*msh)->env));
	ft_memdel((void**)&(*msh)->command);
	ft_memdel((void**)msh);
	if (exit_code != 1)
		exit (exit_code);
}
