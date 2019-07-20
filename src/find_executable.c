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

void	find_executable(void)
{
    int		i;
    char	**paths;
    char	*exe;
    char	*new;
    t_stat	stat;

    if (!g_msh || !g_msh->tok || !g_msh->tok->content)
	return ;
    i = -1;
    new = NULL;
    exe = g_msh->tok->content;
    if (!(paths = ft_strsplit(find_var(g_msh->env, "PATH"), ':')))
	cleanup(-1, "find_executable");
    while (paths && paths[++i])
    {
	if (ft_strnequ(exe, paths[i], ft_strlen(paths[i])))
	    new = ft_strdup(exe);
	else
	    new = find_exec_join(paths[i], exe);
	if (lstat(new, &stat) == -1)
	    ft_memdel((void**)&new);
	else
	{
	    ft_memdel((void**)&(g_msh->tok->content));
	    g_msh->tok->content = new;
	    ft_free_table(&paths); 
	    return ;
	}
    }
   ft_free_table(&paths); 
}
