/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:42:37 by tcase             #+#    #+#             */
/*   Updated: 2019/07/26 20:44:09 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmp_var(t_var *var, char *data_ref)
{
	return (ft_strcmp(var->name, data_ref));
}

void		set_var(t_list *list, char *var_name, char *new_value)
{
	t_var	*var;

	if (!list || !list->content || !var_name)
		return ;
	while (list)
	{
		var = list->content;
		if (!ft_strcmp(var->name, var_name))
		{
			ft_memdel((void**)&var->value);
			var->value = ft_strdup(new_value);
		}
		list = list->next;
	}
}

void		add_var(char *name, char *value, t_list **alist)
{
	t_list	*new_list;
	t_var	*new;
	size_t	size;

	size = sizeof(t_var);
	if (!(new = (t_var*)malloc(size)))
		cleanup(-1, "Malloc failed at create_var");
	if (!(new->name = ft_strdup(name)))
		cleanup(-1, "Malloc failed at create_var 2");
	if (!(new->value = ft_strdup(value)))
		cleanup(-1, "Malloc failed at create_var 3");
	if (!(new_list = ft_lstnew(new, size)))
		cleanup(-1, "Malloc failed at create_var 4");
	ft_memdel((void**)&new);
	ft_lstadd_last(alist, new_list);
}

void		print_var(t_list *list)
{
	t_var *var;

	if (!list || !list->content)
		return ;
	var = list->content;
	ft_printf("%s=%s\n", var->name, var->value);
}

void		delete_var(void *content, size_t size)
{
	t_var	*var;

	if (!content)
		return ;
	var = content;
	ft_memdel((void**)&(var->name));
	ft_memdel((void**)&(var->value));
	ft_memdel((void**)&content);
	size = 0;
}
