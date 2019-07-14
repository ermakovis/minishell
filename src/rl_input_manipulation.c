#include "minishell.h"

void	    rl_print_char(char ch)
{
    t_rl    *rl;

    rl = g_msh->rl;
    realloc_check(&(rl->line), rl->line_len);
    ft_printf("%s", g_msh->cmd->insert_mode_on);
    ft_printf("%c", ch);
    if (rl->cur_pos != rl->line_len)
	ft_memmove(&(rl->line[rl->cur_pos + 1]), &(rl->line[rl->cur_pos]),\
		rl->line_len - rl->cur_pos);
    rl->line[rl->cur_pos] = ch;
    rl->line_len++;
    rl->cur_pos++;
    ft_printf("%s", g_msh->cmd->insert_mode_off);
}


void	    rl_move_cur(long ch)
{
    t_rl    *rl;

    rl = g_msh->rl;
    if (ch == LEFT && rl->cur_pos > 0 && rl->line[rl->cur_pos - 1] != '\n')
    {
	ft_printf("%s", g_msh->cmd->left);
	rl->cur_pos--;
    }
    else if (ch == RIGHT && rl->cur_pos < rl->line_len)
    {
	ft_printf("%s", g_msh->cmd->right);
	rl->cur_pos++;
    }
}

/*
** rl->line[rl->cur_pos - 1] != '\n' to prevent deletion of "dqoute>"
*/

void	    rl_del_char(long ch)
{
    t_rl    *rl;


    rl = g_msh->rl;
    if (ch == DELETE && rl->cur_pos < rl->line_len)
    {
	ft_memmove(&(rl->line[rl->cur_pos]), &(rl->line[rl->cur_pos + 1]),\
		rl->line_len - rl->cur_pos);
	rl->line[rl->line_len - 1] = 0;
	rl->line_len--;
	ft_printf("%s", g_msh->cmd->del);
    }
    else if (ch == BSPACE && rl->cur_pos > 0 && rl->line[rl->cur_pos - 1] != '\n')
    {
	ft_memmove(&(rl->line[rl->cur_pos - 1]), &(rl->line[rl->cur_pos]),\
		rl->line_len - rl->cur_pos);
	rl->line[rl->line_len - 1] = 0;
	rl->cur_pos--;
	rl->line_len--;
	ft_printf("%s%s", g_msh->cmd->left, g_msh->cmd->del);
    }
}
