/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut_str_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:02:50 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 14:05:47 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		printl_str(t_list *list)
{
	ft_printf("%s\n", list->content);
}

void		delete_str(void *content, size_t size)
{
	ft_memdel(&content);
	size = 0;
}
