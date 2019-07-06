/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:51:28 by tcase             #+#    #+#             */
/*   Updated: 2019/07/06 21:55:21 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void realloc_check(char **str, int i, int *buff_size, t_msh *msh)
{
	char *tmp;

	tmp = *str;
	if (i < (*buff_size) - 1)
		return ;
	*buff_size += MSH_BUFF_SIZE;
	if (!(tmp = ft_notrealloc(tmp, i, (*buff_size)))) 
	{
		ft_memdel((void**)str);
		cleanup(&msh, -1, "Failed to realloc for command");
	}
	*str = tmp;
}

static void handle_single_quote(char **str, int *i, int *buff,  t_msh *msh)
{
	char	ch;

	while ((ch = ft_getchar()) != '\'')
	{
		if (ch != 0) 
			(*str)[++(*i)] = ch;
		else
			cleanup(&msh, -1, "No match for quotes\n");
		if (ch == '\n')
			ft_printf("quote> ");
		realloc_check(str, ft_strlen(*str), buff, msh);
	}
}

static void handle_double_quote(char **str, int *i, int *buff, t_msh *msh)
{
	char	ch;
	
	while ((ch = ft_getchar()) != '\"')
	{
		if (ch != 0) 
			(*str)[++(*i)] = ch;
		else
			cleanup(&msh, -1, "No match for quotes\n");
		if (ch == '\n')
			ft_printf("dquote> ");
		realloc_check(str, ft_strlen(*str), buff, msh);
	}
}

int		process_tokens(t_msh *msh)
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
		if (ch == '\\' && (ch = ft_getchar()))
			ch != '\n' ? str[++i] = ch : 1;
		else if (ch == 0 || ch == '\n')
			return(add_token(&str, &i, msh));
		else if (ch == ' ')
		{
			if (i > 0)
				add_token(&str, &i, msh);
		}
		else if (ch == '\'')
			handle_single_quote(&str, &i, &buff_size, msh);
		else if (ch == '\"')
			handle_double_quote(&str, &i, &buff_size, msh);
		else
			str[++i] = ch;
		realloc_check(&str, ft_strlen(str), &buff_size, msh);
	}
	return (0);
}
