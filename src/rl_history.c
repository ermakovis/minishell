#include "minishell.h"

void	rl_add_history(void)
{
    t_list  *new;
    char    *str;

    str = g_msh->rl->line;
    if (!str || !*str)
	return;
    if (!(new = ft_lstnew(str, ft_strlen(str) + 1)))
	cleanup(-1, "Malloc failed at add_token");
    ft_lstadd(&(g_msh->history), new); 
}


void	rl_history(long ch)
{
    t_rl    *rl;
    int	    size;

    if (!(ch == UP || ch == DOWN))
	return ;
    if (!g_msh->history || !g_msh->history->content)
	return ;
    rl = g_msh->rl;
    size = ft_lstsize(g_msh->history) - 1;
    if (ch == UP && rl->history < size)
	rl_history_change(++(rl->history));
    else if (ch == DOWN && rl->history >= 0)
	rl_history_change(--(rl->history));
}
