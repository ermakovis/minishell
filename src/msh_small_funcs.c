#include "minishell.h"

void	msh_exit()
{
    cleanup(0, NULL);
    exit (1);
}
