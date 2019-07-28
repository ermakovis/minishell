/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:58:12 by tcase             #+#    #+#             */
/*   Updated: 2019/07/26 19:01:42 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cl_term_cmd_struct(void)
{
	t_cmd	*cmd;

	if (!g_msh->cmd)
		return ;
	cmd = g_msh->cmd;
	ft_memdel((void**)&cmd->area);
	ft_memdel((void**)&g_msh->cmd);
}

void		cl_rl_struct(void)
{
	if (!g_msh->rl)
		return ;
	ft_memdel((void**)&g_msh->rl->line);
	ft_memdel((void**)&g_msh->rl->history_orig);
	ft_memdel((void**)&g_msh->rl);
}

void		cl_lch_struct(void)
{
	t_lch	*lch;

	if (!g_msh->lch)
		return ;
	lch = g_msh->lch;
	ft_free_table(&lch->env);
	ft_free_table(&lch->tokens);
	ft_memdel((void**)&g_msh->lch);
}

void		cleanup(int exit_code, char *message)
{
	if (message)
		ft_dprintf(2, "%s\n", message);
	if (!g_msh)
		exit(exit_code);
	cl_rl_struct();
	cl_term_cmd_struct();
	cl_lch_struct();
	ft_lstdel(&(g_msh->history), &delete_str);
	ft_lstdel(&(g_msh->env), &delete_var);
	ft_lstdel(&(g_msh->bin), &delete_builtins);
	ft_memdel((void**)&g_msh->original_state);
	ft_memdel((void**)&g_msh);
	if (exit_code != 1)
		exit(exit_code);
}
