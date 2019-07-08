#include "minishell.h"

int	check_buildins()
{
    t_bin   *bin;

    bin = g_msh->bin;
    while (bin)
    {
	if (!(ft_strcmp(g_msh->tokens[0], bin->name)))
	{
	    bin->func();
	    return (1);
	}
	bin = bin->next;
    }
    return (0);
}

static int	tokens_size()
{
    int		i;
    t_tok	*tmp;

    if (!g_msh)
	return (0);
    i = 0;
    tmp = g_msh->tok;
    while (tmp)
    {
	i++;
	tmp = tmp->next;
    }
    return (i);
}

static int process_tokens_list()
{
    int		i;
    char	**tokens;

    if(!(i = tokens_size()))
	return (0);
    if (!(tokens = (char**)malloc(sizeof(char*) * (i + 1))))
	cleanup(-1, "process_tokens_list");
    bzero(tokens, sizeof(char*) * (i + 1));
    i = -1;
    while (g_msh->tok)
    {
	tokens[++i] = ft_strdup(g_msh->tok->token);
	pop_token();
    }
    g_msh->tokens = tokens;
    return (0);
}

void	print_table(char **table)
{
    int		i;

    if (!table || !*table)
	return ;
    i = -1;
    while (table[++i])
	ft_printf("---%s\n", table[i]);
}

void	launch_program()
{
    pid_t   pid;
    int	    status;

    check_var();
    find_executable();
    process_tokens_list();
    print_table(g_msh->tokens);
    if (!(g_msh->tokens) || !(g_msh->tokens[0]) || check_buildins());
    else if ((pid = fork()) < 0)
	ft_printf("%s: fork failed\n", g_msh->tokens[0]);
    else if (pid == 0)
    {
	if (execve(g_msh->tokens[0], g_msh->tokens, g_msh->env) < 0)
	    ft_printf("%s: command not found\n", g_msh->tokens[0]);
	exit(-1);
    }
    else if (pid > 0)
    {
	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
	    waitpid(pid, &status, WUNTRACED);
    }
    clean_table(&(g_msh->tokens));
}
