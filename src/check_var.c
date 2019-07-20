/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:56:05 by tcase             #+#    #+#             */
/*   Updated: 2019/07/07 16:12:57 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_var(void)
{
    int		i;
    char	*str;
    char	*var_value;

    if (!g_msh || !(g_msh->tok))
	return ;
    i = 0;
    var_value = NULL;
    str = g_msh->tok->content;
    if ((i = ft_strchrlen(str, '=')) == -1)
	return ;
    str[i] = '\0';
    if ((var_value = find_var(g_msh->tok, str)))
    {
	ft_memdel((void**)&var_value);
	var_value = ft_strdup(str + i + 1);
    }
    else
	add_var(str, str + i + 1, &g_msh->var);
    ft_lstpop(&g_msh->var, &del_var);
    check_var();

}
