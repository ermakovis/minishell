/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:56:05 by tcase             #+#    #+#             */
/*   Updated: 2019/07/06 21:09:44 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_vars(t_msh *msh)
{
	t_var *tmp;

	tmp = msh->var;
	while (tmp)
	{
		ft_printf("%s - %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}	

void	add_var(char *var_name, char *value, t_msh *msh)
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

void	check_var(t_msh *msh)
{
	int		i;
	char	*str;

	if (!msh || !(msh->tok))
		return ;
	i = 0;
	str = msh->tok->token;
	if ((i = ft_strchrlen(str, '=')) == -1)
		return ;
	ft_printf("i - %d\n", i);
	str[i] = '\0';
	add_var(str, str + i + 1, msh);
	pop_token(msh);
	print_vars(msh);
	
}
