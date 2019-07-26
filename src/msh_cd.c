/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:12:43 by tcase             #+#    #+#             */
/*   Updated: 2019/07/07 16:56:18 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void msh_cd_change(char *path)
{
    char    *tmp;
    char    cwd[PATH_MAX];
    int	    ret;

    if (!(ret = ft_test_path(path)))
    {
	ft_dprintf(2, "cd: %s: No such file or directory\n", path);
	return ;
    }
    else if (ft_item_type(path) != 2)
    {
	ft_dprintf(2, "cd: %s: Not a directory\n", path);
    }
    else if (!(ret & 1))
    {
	ft_dprintf(2, "cd: %s: Permission denied\n", path);
	return ;
    }
    else if (chdir(path) == -1)
    {
	ft_dprintf(2, "cd: %s: Changing directory failed\n", path);
	return;
    }
    set_var(g_msh->env, "OLDPWD", find_var(g_msh->env, "PWD"));
    set_var(g_msh->env, "PWD", getcwd(cwd, PATH_MAX));
}

void	msh_cd(void)
{
    char    **tokens;
    int	    tokens_count; 

    tokens = g_msh->lch->tokens;
    tokens_count = ft_table_size(tokens);
    if (tokens_count > 2)
	ft_dprintf(2, "cd: Too many arguments\n");
    else if (tokens_count == 1)
	msh_cd_change(find_var(g_msh->env, "HOME"));
    else if (ft_strnequ(tokens[1], "-", 2))
	msh_cd_change(find_var(g_msh->env, "OLDPWD"));
    else
	msh_cd_change(tokens[1]);
}
