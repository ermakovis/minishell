#include "minishell.h"

int		cmp_bins(t_bin *bin, char *data_ref)
{
    return (ft_strcmp(bin->name, data_ref));
}

void	delete_builtins(void *content, size_t size)
{
    t_bin *bin;

    bin = content;
    bin->func = NULL;
    ft_memdel((void**)&(bin->name));
    ft_memdel(&content);
    size = 0;
}

static t_bin	*create_builtin(char *name, void (*func)(void))
{
    t_bin   *new;

    if (!(new = (t_bin*)malloc(sizeof(t_bin))))
	cleanup(-1, "Malloc failed at create_builtin");
    if (!(new->name = ft_strdup(name)))
	cleanup(-1, "Malloc failed at create_builtin 2");
    new->func = func;
    return (new);
}

static void	add_builtin(char *name, void (*func)(void))
{
    t_list  *new_list;
    t_bin   *new_bin;
    size_t  size;

    size = sizeof(t_bin);
    new_bin = create_builtin(name, func);
    if (!(new_list = ft_lstnew(new_bin, size)))
	cleanup(-1, "Malloc failed at add_buildin");	
    ft_lstadd(&(g_msh->bin), new_list);
    ft_memdel((void**)&new_bin);
}

void		init_bins(void)
{
    add_builtin("env", &msh_env);
    add_builtin("exit", &msh_exit);
    add_builtin("setenv", &msh_setenv);
    add_builtin("unsetenv", &msh_unsetenv);
    add_builtin("cd", &msh_cd);
    //ft_lstiter(g_msh->bi n, &print_builtins);
}
