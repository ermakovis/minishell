/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:21:25 by tcase             #+#    #+#             */
/*   Updated: 2019/07/26 19:23:16 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_terminal_raw(void)
{
	t_term	*orig;
	t_term	raw;

	if (!isatty(STDIN_FILENO))
		return ;
	if (!(orig = (t_term*)malloc(sizeof(t_term))))
		cleanup(-1, "Failed to malloc for terminal state structure");
	if (tcgetattr(0, orig) == -1)
		cleanup(-1, "Failed to save terminal original state");
	g_msh->original_state = orig;
	if (tcgetattr(0, &raw) == -1)
		cleanup(-1, "Failed to save terminal original state");
	raw.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &raw) == -1)
		cleanup(-1, "Failed to set terminal to raw mode");
}

void	set_terminal_canon(void)
{
	if (!isatty(STDIN_FILENO))
		return ;
	if (tcsetattr(0, TCSANOW, g_msh->original_state) == -1)
		cleanup(-1, "Failed to set terminal to raw mode");
}

void	handle_sigint(int sig)
{
	if (!g_msh->rl->status)
	{
		ft_printf("\n");
		display_prompt();
	}
	cl_rl_struct();
	init_rl();
}

int		main(int argc, char **argv, char **env)
{
	int		i;
	int		ch;

	init(env);
	set_terminal_raw();
	display_prompt();
	signal(SIGINT, handle_sigint);
	while (read_line())
	{
		rl_add_history();
		parse_line();
		launch_program();
		cl_rl_struct();
		display_prompt();
	}
	set_terminal_canon();
	cleanup(0, NULL);
}
