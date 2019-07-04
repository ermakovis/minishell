#include "minishell.h"

void	msh_exit(t_msh *msh)
{
    cleanup(&msh, 0, NULL);
    exit (1);
}
