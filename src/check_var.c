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

static void	print_vars(t_msh *msh)
{
	t_var *tmp;

	tmp = msh->var;
	while (tmp)
	{
		ft_printf("%s - %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}	

static void	add_var(char *var_name, char *value, t_msh *msh)
{
	t_var	*var;
	t_var	*tmp_var;

	if (!(var = (t_var*)malloc(sizeof(t_var))))
		cleanup(&msh, -1, "add_var_1");
	ft_bzero(var, sizeof(t_var));
	tmp_var = msh->var;
	if (!(var->name = ft_strdup(var_name)))
		cleanup(&msh, -1, "add_var_2");
	if (!(var->value = ft_strdup(value)))
		cleanup(&msh, -1, "add_var_3");
	if (!tmp_var)
	{
		msh->var = var;
		return;
	}
	while (tmp_var->next)
		tmp_var = tmp_var->next;
	tmp_var->next = var;
}

static int		set_var(char *var_name, char *value, t_msh *msh)
{
	t_var	*tmp;

	if (!msh || !msh->var)
		return (1);
	tmp = msh->var;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, var_name))
		{
			ft_memdel((void**)&(tmp->value));
			if (!(tmp->value = ft_strdup(value)))
				cleanup(&msh, -1, "set_var");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void		check_var(t_msh *msh)
{
	int		i;
	char	*str;

	if (!msh || !(msh->tok))
		return ;
	i = 0;
	str = msh->tok->token;
	if ((i = ft_strchrlen(str, '=')) == -1)
		return ;
	str[i] = '\0';
	if (set_var(str, str + i + 1, msh))
		add_var(str, str + i + 1, msh);
	pop_token(msh);
	print_vars(msh);
	
}
