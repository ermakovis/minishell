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

void realloc_check(char **str, int old_size)
{
    int		new_size;
    char	*tmp;

    if (!old_size || old_size % MSH_BUFF_SIZE != 0)
	return ;
    tmp = *str;
    new_size = ((old_size / MSH_BUFF_SIZE) + 1) * MSH_BUFF_SIZE;
    if (!(tmp = ft_notrealloc(tmp, old_size, new_size))) 
    {
	ft_memdel((void**)str);
	cleanup(-1, "Failed to realloc for command");
    }
    *str = tmp;
}

int		process_tokens()
{
    int		i;
    int		ch;
    int		buff_size;
    char	*str;

    i = -1;
    str = NULL;
    buff_size = MSH_BUFF_SIZE;
    while((ch = ft_getchar()) >= 0) 
    {
	if (!str)
	    str = ft_strnew(MSH_BUFF_SIZE);
	if ((ch == '~' && !str[i]) || ch == '$')
	    process_tokens_expans(&str, &i, &ch);
	if (ch == '\'' || ch == '\"' || ch == '\\')
	    process_tokens_quotes(&str, &i, ch);
	else if (ch == 0 || ch == '\n')
	    return(add_token(&str, &i));
	else if (ch == ' ' || ch == '\t')
	    add_token(&str, &i);
	else
	    str[++i] = ch;
	realloc_check(&str, i + 1);
    }
    return (0);
}
