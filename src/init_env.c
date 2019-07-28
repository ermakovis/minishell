/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:14:30 by tcase             #+#    #+#             */
/*   Updated: 2019/07/26 19:16:23 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(t_list *list, char *var_name)
{
	t_var	*var;

	if (!list || !list->content || !var_name)
		return (NULL);
	while (list)
	{
		var = list->content;
		if (!ft_strcmp(var->name, var_name))
			return (var->value);
		list = list->next;
	}
	return (NULL);
}

void	init_env(char **env)
{
	t_list	*new;
	t_var	*var;
	int		i;
	size_t	equal_pos;

	i = -1;
	while (env[++i])
	{
		if ((equal_pos = ft_strchrlen(env[i], '=')) == -1)
			continue ;
		env[i][equal_pos] = '\0';
		add_var(&(env[i][0]), &(env[i][equal_pos + 1]), &g_msh->env);
	}
}
