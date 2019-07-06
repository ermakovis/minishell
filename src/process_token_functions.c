/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:51:14 by tcase             #+#    #+#             */
/*   Updated: 2019/07/06 21:05:31 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_token(t_msh *msh)
{
	t_tok *next;

	if (!msh || !(msh->tok) || !(msh->tok->token))
		return ;
	next = msh->tok->next;
	ft_memdel((void**)&(msh->tok->token));
	ft_memdel((void**)&(msh->tok));
	msh->tok = next;
}

int		add_token(char **str, int *i, t_msh *msh)
{
	t_tok	*new;
	t_tok	*tmp;

	*i = -1;
	if (ft_strlen(*str) < 1)
		return (1) ;
	if (!(new = (t_tok*)malloc(sizeof(t_tok))))
		cleanup(&msh, -1, "Token malloc failed");
	ft_bzero(new, sizeof(t_tok));
	new->token = ft_strdup(*str);
	ft_memdel((void**)str);
	if(!(*str = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(&msh, -1, "add_token");
	if (!(msh->tok))
	{
		msh->tok = new;
		return (1);
	}
	tmp = msh->tok;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

