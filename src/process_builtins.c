#include "minishell.h"

void	add_builtin(char *name, void (*func)(t_msh*), t_bin **bin)
{
	t_bin *new;
	t_bin *tmp;

	if (!(new = (t_bin*)malloc(sizeof(t_bin))))
		return ;
	ft_bzero(new, sizeof(t_bin));
	new->name = ft_strdup(name);
	new->func = func;
	new->next = NULL;
	if (!*bin)
	{
		*bin = new;
		return ;
	}
	tmp = *bin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	process_builtins(t_msh *msh)
{
	t_bin   *new;

	new = NULL;
	add_builtin("env", &msh_env, &new);
	add_builtin("setenv", &msh_setenv, &new);
	add_builtin("unsetenv", &msh_unsetenv, &new);
	add_builtin("exit", &msh_exit, &new);
	msh->bin = new;
}
