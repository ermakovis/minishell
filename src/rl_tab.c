/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:36:53 by tcase             #+#    #+#             */
/*   Updated: 2019/07/31 13:35:34 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*rl_tab_lastword(void)
{
	int		i;
	char	*str;
	char	*ret;

	i = 0;
	ret = NULL;
	str = g_msh->rl->line;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			ret = &str[i];
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (ret);
}

static void		add_entry(char *line)
{
	t_list	*new;

	if (!line || !*line)
		return ;
	if (!(new = ft_lstnew(line, ft_strlen(line) + 1)))
		cleanup(-1, "Malloc failed at add_token");
	ft_lstadd_last(&(g_msh->rl->tab_items), new);
}

static void		rl_tab_create_list(char **paths, char *line)
{
	DIR		*dir;
	t_dir	*entry;
	int		i;

	i = -1;
	while (paths[++i])
	{
		if (!(dir = opendir(paths[i])))
			continue ;
		while ((entry = readdir(dir)))
		{
			if (!ft_strncmp(entry->d_name, line, ft_strlen(line)))
				add_entry(entry->d_name);
		}
		closedir(dir);
	}
	return ;
}

static char		rl_tab_check_char(void)
{
	t_list		*tmp_list;
	int			line_len;
	char		*str;
	char		ch;

	line_len = ft_strlen(rl_tab_lastword());
	ch = ((char*)g_msh->rl->tab_items->content)[line_len];
	tmp_list = g_msh->rl->tab_items;
	while (tmp_list)
	{
		str = tmp_list->content;
		if (str[line_len] != ch)
			return (0);
		tmp_list = tmp_list->next;
	}
	return (ch);
}

void			rl_tab(long ch)
{
	char	*path_str;
	char	**paths;
	char	nch;

	nch = 0;
	if (ch != TAB || !(path_str = find_var(g_msh->env, "PATH")))
		return ;
	if (!g_msh->rl->line)
		return ;
	if (!(paths = ft_strsplit(path_str, ':')))
		cleanup(-1, "rl_tab");
	rl_tab_create_list(paths, rl_tab_lastword());
	if (!g_msh->rl->tab_items)
	{
		ft_free_table(&paths);
		return ;
	}
	ft_lst_sort(&(g_msh->rl->tab_items), &ft_strcmp);
	while ((nch = rl_tab_check_char()))
		rl_print_char(nch);
	if (ft_lstsize(g_msh->rl->tab_items) == 1 &&\
			!ft_strcmp(g_msh->rl->tab_items->content, g_msh->rl->line))
		rl_print_char(' ');
	ft_lstdel(&(g_msh->rl->tab_items), &delete_str);
	ft_free_table(&paths);
}
