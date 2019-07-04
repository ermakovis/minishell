#include "minishell.h"

int	check_buildins(t_msh *msh)
{
    t_bin   *bin;

    bin = msh->bin;
    while (bin)
    {
	if (!(ft_strcmp(msh->tokens[0], bin->name)))
	{
	    bin->func(msh);
	    return (1);
	}
	bin = bin->next;
    }
    return (0);
}

void	launch_program(t_msh *msh)
{
    pid_t   pid;
    int	    status;
    int	    i;

    if (!(msh->tokens) || check_buildins(msh))
        return ;
    if ((pid = fork()) < 0)
    {
	ft_printf("%s: fork failed\n", msh->tokens[0]);
	return ;
    }
    if (pid == 0)
    {
	if (execve(msh->tokens[0], msh->tokens, msh->env) < 0)
	    ft_printf("%s: command not found\n", msh->tokens[0]);
	exit(-1);
    }
    if (pid > 0)
    {
	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
	    waitpid(pid, &status, WUNTRACED);
    }
}
