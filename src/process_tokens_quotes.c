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

void	process_tokens_bslash(char **str, int *i, char **line)
{
    (*line)++;
    if (!(**line))
	return ;
    if (**line != '\n')
	(*str)[++(*i)] = **line;
}

void	process_tokens_squote(char **str, int *i, char **line)
{
    while (**line)
    {
	if (**line != 0) 
	    (*str)[++(*i)] = **line;
	else
	    cleanup(-1, "No match for quotes\n");
	realloc_check(str, *i + 1);
	(*line)++;
    }
}

void	process_tokens_dquote(char **str, int *i, char **line)
{
    while (**line)
    {
	if (**line == '$')
	    process_tokens_expans_dsign(str, i, line);
	if (**line == '\"')
	    return ;
	if (**line == '\\')
	    process_tokens_bslash(str, i, line);
	else if (*line != 0) 
	    (*str)[++(*i)] = **line;
	else
	    cleanup(-1, "No match for quotes\n");
	realloc_check(str, *i + 1);
	(*line)++;
    }
}

void	process_tokens_quotes(char **str, int *i, char **line)
{
    if (**line == '\\')
	process_tokens_bslash(str, i, line);
    else if (**line == '\"')
	process_tokens_dquote(str, i, line);
    else if (**line == '\'')
	process_tokens_squote(str, i, line);

}
