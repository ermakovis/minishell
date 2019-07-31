#include "minishell.h"

static	void	rl_jump_word_next(long ch)
{
	int		i;
	char	*line;

	if (ch != WORD_NEXT || g_msh->rl->line_len == g_msh->rl->cur_pos)
		return ;
	i = g_msh->rl->cur_pos;
	line = g_msh->rl->line;
	if (!(ft_strchr(line, ' ')))
		return ;
	while (line[i] != ' ')
	{
		rl_move_cur(RIGHT);
		i++;
	}
	while (line[i] == ' ')
	{
		rl_move_cur(RIGHT);
		i++;
	}
}

static	void	rl_jump_word_back(long ch)
{
	int		i;
	char	*line;

	if (ch != WORD_BACK || g_msh->rl->cur_pos == 0)
		return ;
	i = g_msh->rl->cur_pos;
	line = g_msh->rl->line;
	while (i > 0 && line[i - 1] == ' ')
	{
		rl_move_cur(LEFT);
		i--;
	}
	while (i > 0 && line[i - 1] != ' ') 
	{
		rl_move_cur(LEFT);
		i--;
	}
}
void			rl_jump(long ch)
{
	if (!(ch == LINE_START || ch == LINE_END ||\
		ch == WORD_NEXT || ch == WORD_BACK))
		return ;
	rl_jump_word_next(ch);
	rl_jump_word_back(ch);
	if (ch == LINE_START)
	{
		while (g_msh->rl->cur_pos)
			rl_move_cur(LEFT);
	}
	if (ch == LINE_END)
	{
		while (g_msh->rl->cur_pos != g_msh->rl->line_len)
			rl_move_cur(RIGHT);
	}
}
