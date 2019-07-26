/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:57:09 by tcase             #+#    #+#             */
/*   Updated: 2019/07/07 17:46:50 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_exec_join(char *s1, char *s2)
{
    char	*join;
    int		s1len;
    int		s2len;

    if (!s1 && !s2)
	return (NULL);
    s1len = ft_strlen(s1);
    s2len = ft_strlen(s2);
    if (!(join = ft_strnew(s1len + s2len + 1)))
	return (NULL);
    ft_memcpy(join, s1, s1len);
    if (*(join + s1len) != '/')
	ft_memset(join + s1len, '/', 1);
    ft_memcpy(join + s1len + 1, s2, s2len);
    return (join);
}

static int  check_bins(char *str)
{
    if (ft_lst_find(g_msh->bin, str, &cmp_bins))
	return (1);
    return (0);
}

static void get_full_path(char *path, char **new)
{
    char    *exe;

    exe = g_msh->tok->content;
    if (ft_strnequ(exe, path, ft_strlen(path)))
	*new = ft_strdup(exe);
    else
	*new = find_exec_join(path, exe);
}

static int  check_full_path(char **new)
{
    if (!ft_test_path(*new))
    {
	ft_memdel((void**)new);
	return (0);
    }
    else
    {
	ft_memdel((void**)&(g_msh->tok->content));
	g_msh->tok->content = *new;
	return (1);
    }
}

void	find_executable(void)
{
    int		i;
    char	**paths;
    char	*paths_env;
    char	*new;

    if (!g_msh || !g_msh->tok || !g_msh->tok->content)
	return ;
    if (check_bins(g_msh->tok->content))
	return ;
    if (!(paths_env = find_var(g_msh->env, "PATH")))
	return ;
    i = -1;
    new = NULL;
    if (!(paths = ft_strsplit(paths_env, ':')))
	cleanup(-1, "find_executable");
    while (paths[++i])
    {
	get_full_path(paths[i], &new);
	if (check_full_path(&new))
	    break ;
    }
    ft_free_table(&paths); 
}
