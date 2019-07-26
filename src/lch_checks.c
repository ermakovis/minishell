#include "minishell.h"

int	lch_check_bins(void)
{
    t_list  *list;
    t_bin   *bin;
    char    **tokens;

    tokens = g_msh->lch->tokens;
    if (!tokens || !*tokens)
	return (1);
    list = g_msh->bin;
    while (list)
    {
	bin = list->content;	
	if (!(ft_strcmp(tokens[0], bin->name)))
	{
	    bin->func();
	    return (1);
	}
	list = list->next;
    }
    return (0);
}

void		lch_check_var(void)
{
    int		i;
    char	*str;

    if (!g_msh || !(g_msh->tok))
	return ;
    i = 0;
    str = g_msh->tok->content;
    if ((i = ft_strchrlen(str, '=')) < 1)
	return ;
    str[i] = '\0';
    if (find_var(g_msh->env, str))
	set_var(g_msh->env, str, str + i + 1);
    else if (find_var(g_msh->var, str))
	set_var(g_msh->var, str, str + i + 1);
    else
	add_var(str, str + i + 1, &(g_msh->var));
    ft_lstpop(&g_msh->tok, &delete_str);
    lch_check_var();
}

void	    lch_env(void)
{
    int	    i;
    char    **env;
    t_list   *env_list;
    size_t  size;

    i = -1;
    env_list = g_msh->env;
    size = ft_lstsize(env_list);
    if (!(env = (char**)malloc(sizeof(char*) * (size + 1))))
	cleanup(-1, "Malloc failed at process_env_list");
    ft_bzero(env, sizeof(char*) * (size + 1));
    while (env_list)
    {
	env[++i] = var_to_str(env_list->content);
	env_list = env_list->next;
    }
    g_msh->lch->env = env;
}

void	    lch_tokens(void)
{
    int		i;
    int		check;
    char	**tokens;

    if(!(i = ft_lstsize(g_msh->tok)))
	return ;
    if (!(tokens = (char**)malloc(sizeof(char*) * (i + 1))))
	cleanup(-1, "process_tokens_list");
    bzero(tokens, sizeof(char*) * (i + 1));
    i = -1;
    while (g_msh->tok && (check = ft_strcmp(g_msh->tok->content, ";")))
    {
	tokens[++i] = ft_strdup(g_msh->tok->content);
	ft_lstpop(&(g_msh->tok), &delete_str);
    }
    if (check == 0)
	ft_lstpop(&(g_msh->tok), &delete_str);
    g_msh->lch->tokens = tokens;
}
