/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:51:28 by tcase             #+#    #+#             */
/*   Updated: 2019/07/07 16:38:12 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		process_tokens(char *line)
{
    int		i;
    char	*str;

    i = -1;
    str = NULL;
    while(line) 
    {
	if (!str)
	    str = ft_strnew(MSH_BUFF_SIZE);
	if ((*line == '~' && !str[i]) || *line == '$')
	    process_tokens_expans(&str, &i, &line);
	if (*line == '\'' || *line == '\"' || *line == '\\')
	    process_tokens_quotes(&str, &i, &line);
	else if (*line == 0 || *line == '\n')
	    return(add_token(&str, &i));
	else if (*line == ' ' || *line == '\t')
	    add_token(&str, &i);
	else
	    str[++i] = *line;
	realloc_check(&str, i + 1);
	line++;
    }
    return (0);
}
