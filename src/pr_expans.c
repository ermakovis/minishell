#include "minishell.h"

static int	   is_special(char ch)
{
    if (ch == '\n' || ch == '\'' || ch == '\"'\
	|| ch == '\\' || ch == ' ' || ch == '$'\
	|| ch == '\t')
	return (1);
    return (0);
}

void		    pr_expans_dsign(char **token, int *i, char **line)
{
    int	    j;
    char    var_name[NAME_MAX + 1];

    j = 0;
    ft_bzero(var_name, NAME_MAX + 1);
    while(**line && !is_special(**line) && j < NAME_MAX)
    {	
	var_name[j++] == **line;
	(*line)++;
    }
    append_str(token, i, find_var(g_msh->var, var_name));
}

void		    pr_expans_tild(char **token, int *i, char **line)
{
    (*line)++;
    if (**line == '+')
	append_str(token, i, find_var(g_msh->env, "PWD"));
    else if (**line == '-')
	append_str(token, i, find_var(g_msh->env, "OLDPWD"));
    else
	append_str(token, i, find_var(g_msh->env, "HOME"));
    if (**line == '\\')
	(*token)[++(*i)] == '\\';
    if ((**line == '+' || **line == '-') && *((*line)++) =='\\')
	(*token)[++(*i)] == '\\';
}

void		    pr_expans(char **token, int *i, char **line)
{
    if (**line == '~')
	pr_expans_tild(token, i, line);
    else if (**line == '$')
	pr_expans_dsign(token, i, line);
}