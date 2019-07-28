/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:47:46 by tcase             #+#    #+#             */
/*   Updated: 2019/07/26 21:05:16 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pr_quotes_bslash(char **token, int *i, char **line)
{
	(*line)++;
	realloc_check(token, *i);
	if (**line != '\n')
		(*token)[(*i)++] = **line;
}

void		pr_quotes_single(char **token, int *i, char **line)
{
	(*line)++;
	while (**line && **line != '\'')
	{
		realloc_check(token, *i);
		(*token)[(*i)++] = **line;
		(*line)++;
	}
}

void		pr_quotes_double(char **token, int *i, char **line)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		realloc_check(token, *i);
		if (**line == '$')
			pr_expans_dsign(token, i, line);
		else if (**line == '\\')
			pr_quotes_bslash(token, i, line);
		else
			(*token)[(*i)++] = **line;
		(*line)++;
	}
}

void		pr_quotes(char **token, int *i, char **line)
{
	if (**line == '\'')
		pr_quotes_single(token, i, line);
	else if (**line == '\"')
		pr_quotes_double(token, i, line);
	else if (**line == '\\')
		pr_quotes_bslash(token, i, line);
}
