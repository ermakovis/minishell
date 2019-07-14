#include "minishell.h"

void	    init_msh(void)
{
    t_msh   *new_msh;

    if (!(new_msh = (t_msh*)malloc(sizeof(t_msh))))
	cleanup(-1, "Failed to malloc for main structure\n");
    g_msh = new_msh;
}
