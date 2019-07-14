#include "minishell.h"

static void	    print_list(t_list *list)
{
    ft_printf("%s\n", list->content);
}

void	    delete_env(void *content, size_t size)
{
    ft_memdel(&content);
    size = 0;
}

void		    process_env(char **env)
{
    t_list	*env_list;
    t_list	*new;
    int	    i;

    i = -1;
    env_list = NULL;
    while(env[++i])
    {
	if (!(new = ft_lstnew(env[i], ft_strlen(env[i]) + 1)))
	    cleanup(-1, "Failed to process env variables\n");
	ft_lstadd(&env_list, new); 
    }
    g_msh->env = env_list;
}
