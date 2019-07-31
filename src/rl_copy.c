#include "minishell.h"

void	rl_copy(long ch)
{
	if (ch != VISUAL_MODE)
		return ;
	ft_printf("--");
	ft_printf("%s", g_msh->cmd->highlight_mode_on);
	while(get_char(&ch))
	{
		if (ch == 'y')
			return ;
		rl_move_cur(ch);
		rl_jump(ch);
		ch = 0;
	}
	
	ft_printf("%s", g_msh->cmd->highlight_mode_off);

}
