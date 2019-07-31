/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:31:12 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 16:00:42 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(char **token, int *i)
{
	t_list	*new;

	if (!token || !*token || !**token)
		return ;
	if (!(new = ft_lstnew(*token, ft_strlen(*token) + 1)))
		cleanup(-1, "Malloc failed at add_token");
	ft_lstadd_last(&(g_msh->tok), new);
	ft_memdel((void**)token);
	*i = 0;
}

static void	pr_semicol(char **token, int *i, char **line)
{
	add_token(token, i);
	if (!(*token = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(-1, "Malloc failed at pr_semicol");
	(*token)[(*i)++] = **line;
	add_token(token, i);
}

void		pr_param_switch(char **token, int *i, char **line)
{
	if ((**line == '~' && !(*token)[0]) || **line == '$')
		pr_expans(token, i, line);
	else if (**line == '\'' || **line == '\"' || **line == '\\')
		pr_quotes(token, i, line);
	else if (**line == ' ' || **line == '\t')
		add_token(token, i);
	else if (**line == ';')
		pr_semicol(token, i, line);
	else
		(*token)[(*i)++] = **line;
}

void		parse_line(void)
{
	int		i;
	char	*line;
	char	*token;

	if (!g_msh->rl->line)
		return ;
	i = 0;
	token = NULL;
	line = g_msh->rl->line;
	while (*line)
	{
		if (!token)
			if (!(token = ft_strnew(MSH_BUFF_SIZE)))
				cleanup(-1, "Malloc failed at parser");
		realloc_check(&token, i);
		pr_param_switch(&token, &i, &line);
		line++;
	}
	add_token(&token, &i);
	ft_memdel((void**)&token);
}
