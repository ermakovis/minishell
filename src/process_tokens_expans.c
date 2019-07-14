/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token_expans.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:34:57 by tcase             #+#    #+#             */
/*   Updated: 2019/07/07 16:38:19 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_special(char ch)
{
    if (ch == '\n' || ch == '\'' || ch == '\"'\
	    || ch == '\\' || ch == ' ' || ch == '$'\
	    || ch == '\t')
	return (1);
    return (0);
}

static void		append_str(char **str, int *i, char *new)
{
    int		j;
    int		k;

    j = -1;
    while (new[++j])
    {
	realloc_check(str, *i + 1);
	(*str)[++(*i)] = new[j];
    }
}

void		process_tokens_expans_tild(char **str, int *i, char **line)
{
    if ((*str)[*i] != 0) 
	return ;
    (*line)++;
    if (**line == '+')
	append_str(str, i, parse_env("PWD=", g_msh->env));
    else if (**line == '-')
	append_str(str, i, parse_env("OLDPWD=", g_msh->env));
    else 
	append_str(str, i, parse_env("HOME=", g_msh->env));
    if (**line == '\\')
	(*str)[++(*i)] = '\\';
    if ((**line == '+' || **line == '-') && *((*line)++) == '\\')
	(*str)[++(*i)] = '\\';
}

void		process_tokens_expans_dsign_append(char **str,\
	int *i, char *var_name)
{
    t_var	*tmp_var;

    tmp_var = g_msh->var;
    while (tmp_var)
    {
	if (!(ft_strcmp(tmp_var->name, var_name)))
	{
	    append_str(str, i, tmp_var->value);
	    return ;
	}
	tmp_var = tmp_var->next;
    }
}

void		process_tokens_expans_dsign(char **str, int *i,\
	char **line)
{
    int		j;
    char	var_name[NAME_MAX];

    j = 0;
    ft_bzero(var_name, NAME_MAX);
    while (**line)
    {
	if (is_special(**line))
	    break ;
	var_name[j] = **line;
	if (++j == NAME_MAX)
	    cleanup(-1, "Too long var name");
	(*line)++;
    }
    process_tokens_expans_dsign_append(str, i, var_name);
}

void			process_tokens_expans(char **str, int *i, char **line)
{
    if (**line == '~')
	process_tokens_expans_tild(str, i, line);
    while(**line == '$')
	process_tokens_expans_dsign(str, i, line);	

}
