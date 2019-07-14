#include "minishell.h"

void	    add_var(char *name, char *value)
{
    t_list  *new_list;
    t_var   *new;
    size_t  size;

    size = sizeof(t_var);
    if (!(new = (t_var*)malloc(size)))
	cleanup(-1, "Malloc failed at create_var");
    if (!(new->name = ft_strdup(name)))
	cleanup(-1, "Malloc failed at create_var 2");
    if (!(new->value = ft_strdup(value)))
	cleanup(-1, "Malloc failed at create_var 3");
    if (!(new_list = ft_lstnew(new, size)))
	cleanup(-1, "Malloc failed at create_var 4");
    ft_lstadd(&(g_msh->env), new_list);
}

void	    print_var(t_list *list)
{
    t_var *var;

    var = list->content;
    ft_printf("%s - %s\n", var->name, var->value);
}

void	    delete_var(void *content, size_t size)
{
    t_var   *var;

    var = content;
    ft_memdel((void**)&(var->name));
    ft_memdel((void**)&(var->value));
    ft_memdel(&content);
    size = 0;
}

char	    *find_var(t_list *list, char *var_name)
{
    t_var   *var;

    while (list)
    {
	var = list->content;
	if (!ft_strcmp(var->name, var_name))
	    return (var->value);
	list = list->next;
    }
    return (NULL);
}

void		    process_env(char **env)
{
    t_list	*new;
    t_var	*var;
    int		i;
    size_t	equal_pos;

    i = -1;
    while(env[++i])
    {
	if ((equal_pos = ft_strchrlen(env[i], '=')) == -1)
	    continue ;
	env[i][equal_pos] = '\0';
	add_var(&(env[i][0]), &(env[i][equal_pos + 1]));
    }
//    ft_lstiter(g_msh->env, &print_var);
}
