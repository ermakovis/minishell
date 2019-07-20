#include "minishell.h"

int	check_buildins(char **tokens)
{
    t_list  *list;
    t_bin   *bin;

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

void		check_var(void)
{
    int		i;
    char	*str;
    char	*var_value;

    if (!g_msh || !(g_msh->tok))
	return ;
    i = 0;
    var_value = NULL;
    str = g_msh->tok->content;
    if ((i = ft_strchrlen(str, '=')) < 1)
	return ;
    str[i] = '\0';
    if ((var_value = find_var(g_msh->var, str)))
    {
	ft_memdel((void**)&var_value);
	var_value = ft_strdup(str + i + 1);
    }
    else
	add_var(str, str + i + 1, &(g_msh->var));
    ft_lstpop(&g_msh->tok, &delete_str);
    check_var();
}

void	    process_env_list(void)
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

void	    process_tokens_list(void)
{
    int		i;
    char	**tokens;

    if(!(i = ft_lstsize(g_msh->tok)))
	return ;
    if (!(tokens = (char**)malloc(sizeof(char*) * (i + 1))))
	cleanup(-1, "process_tokens_list");
    bzero(tokens, sizeof(char*) * (i + 1));
    i = -1;
    while (g_msh->tok)
    {
	tokens[++i] = ft_strdup(g_msh->tok->content);
	ft_lstpop(&(g_msh->tok), &delete_str);
    }
    g_msh->lch->tokens = tokens;
}

void	print_table(char **table)
{
    int	    i;

    if (!table && !table)
	return ;
    i = -1;
    while(table[++i])
	ft_printf("--%s\n", table[i]);

}

void	launch_program(void)
{
    pid_t   pid;
    int	    status;
    char    **tokens;

    check_var();
    if (!(g_msh->lch = (t_lch*)malloc(sizeof(t_lch))))
	cleanup(-1, "Malloc failed at init_msh 2");
    ft_bzero(g_msh->lch, sizeof(t_lch));
    find_executable();
    process_tokens_list();
    process_env_list();
    tokens = g_msh->lch->tokens;
    print_table(tokens);
    if (!tokens || !tokens[0] || check_buildins(tokens));
    else if ((pid = fork()) < 0)
	ft_printf("%s: fork failed\n", tokens[0]);
    else if (pid == 0)
    {
	if (execve(tokens[0], tokens, g_msh->lch->env) < 0)
	    ft_printf("%s: command not found\n", tokens[0]);
	exit(-1);
    }
    else if (pid > 0)
    {
	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
	    waitpid(pid, &status, WUNTRACED);
    }
    cl_lch_struct();
}
