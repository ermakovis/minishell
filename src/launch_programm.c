/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_programm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:16:34 by tcase             #+#    #+#             */
/*   Updated: 2019/07/26 19:18:09 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lch(void)
{
	if (!(g_msh->lch = (t_lch*)malloc(sizeof(t_lch))))
		cleanup(-1, "Malloc failed at init_msh 2");
	ft_bzero(g_msh->lch, sizeof(t_lch));
}

static void	lch_launch(void)
{
	int		pid;
	int		status;
	char	**tokens;
	char	**env;

	tokens = g_msh->lch->tokens;
	env = g_msh->lch->env;
	if ((pid = fork()) < 0)
		ft_printf("%s: fork failed\n", tokens[0]);
	else if (pid == 0)
	{
		if (!ft_test_path(tokens[0]))
			ft_dprintf(2, "%s: command not found\n", tokens[0]);
		else if (!(ft_test_path(tokens[0]) & 1))
			ft_dprintf(2, "%s: permission denied\n", tokens[0]);
		else if (execve(tokens[0], tokens, g_msh->lch->env) < 0)
			ft_printf("%s: launch failed\n", tokens[0]);
		exit(-1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}

void		launch_program(void)
{
	if (!g_msh->tok || !g_msh->tok->content)
		return ;
	init_lch();
	lch_check_var();
	find_executable();
	lch_tokens();
	lch_env();
	if (!lch_check_bins())
		lch_launch();
	cl_lch_struct();
	launch_program();
}
