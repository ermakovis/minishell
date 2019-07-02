#include "minishell.h"

void	clean_tokens(char ***tokens)
{
    int	    i;
    char    **tmp;

    i = -1;
    tmp = *tokens;
    while(tmp[++i])
	ft_memdel((void**)&tmp[i]);
    ft_memdel((void**)&tmp);
    *tokens = NULL;
}

void	clean_path(char ***path)
{
    int	    i;
    char    **tmp;

    i = -1;
    tmp = *path;
    while(tmp[++i])
	ft_memdel((void**)&tmp[i]);
    ft_memdel((void**)&tmp);
    *path = NULL;
}


void	cleanup(t_msh **msh, int exit_code, char *message)
{
    if (message)
	ft_dprintf(2, "%s\n", message);
    if (!msh || !*msh)
	exit (exit_code);
    if ((*msh)->env_path)
	clean_path(&((*msh)->env_path));
    if ((*msh)->tokens)
    	clean_tokens(&((*msh)->tokens));
    ft_memdel((void**)&((*msh)->env_cwd));
    ft_memdel((void**)msh);
    if (exit_code != 1)
	exit (exit_code);
}
