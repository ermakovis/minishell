/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_input_manipulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:57:08 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 14:06:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		rl_print_char(char ch)
{
	t_rl	*rl;

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

void		rl_move_cur(long ch)
{
	t_rl	*rl;

	if (!(ch == LEFT || ch == RIGHT))
		return ;
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

void		rl_del_char(long ch)
{
	t_rl	*rl;

	if (!(ch == DELETE || ch == BSPACE))
		return ;
	rl = g_msh->rl;
	if (ch == DELETE && rl->cur_pos < rl->line_len)
	{
		ft_memmove(&(rl->line[rl->cur_pos]), &(rl->line[rl->cur_pos + 1]),\
				rl->line_len - rl->cur_pos);
		rl->line[rl->line_len - 1] = 0;
		rl->line_len--;
		ft_printf("%s", g_msh->cmd->del);
	}
	else if (ch == BSPACE && rl->cur_pos > 0 &&\
			rl->line[rl->cur_pos - 1] != '\n')
	{
		ft_memmove(&(rl->line[rl->cur_pos - 1]), &(rl->line[rl->cur_pos]),\
				rl->line_len - rl->cur_pos);
		rl->line[rl->line_len - 1] = 0;
		rl->cur_pos--;
		rl->line_len--;
		ft_printf("%s%s", g_msh->cmd->left, g_msh->cmd->del);
	}
}
