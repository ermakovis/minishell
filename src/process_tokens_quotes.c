/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 10:08:42 by tcase             #+#    #+#             */
/*   Updated: 2019/07/07 16:38:22 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_tokens_bslash(char **str, int *i)
{
	int	ch;

	if (!(ch = ft_getchar()))
		return ;
	if (ch != '\n')
		(*str)[++(*i)] = ch;
	else
		ft_printf("bslash> ");
}

void	process_tokens_squote(char **str, int *i)
{
	int	ch;

	while ((ch = ft_getchar()) != '\'')
	{
		if (ch != 0) 
			(*str)[++(*i)] = ch;
		else
			cleanup(-1, "No match for quotes\n");
		if (ch == '\n')
			ft_printf("quote> ");
		realloc_check(str, *i + 1);
	}
}

void	process_tokens_dquote(char **str, int *i)
{
	int	ch;

	while ((ch = ft_getchar()) >= 0)
	{
		if (ch == '$')
			process_tokens_expans_dsign(str, i, &ch);
		if (ch == '\"')
			return ;
		if (ch == '\\')
			process_tokens_bslash(str, i);
		else if (ch != 0) 
			(*str)[++(*i)] = ch;
		else
			cleanup(-1, "No match for quotes\n");
		if (ch == '\n')
			ft_printf("dquote> ");
		realloc_check(str, *i + 1);
	}
}

void	process_tokens_quotes(char **str, int *i, int ch)
{
	if (ch == '\\')
		process_tokens_bslash(str, i);
	else if (ch == '\"')
		process_tokens_dquote(str, i);
	else if (ch == '\'')
		process_tokens_squote(str, i);

}
