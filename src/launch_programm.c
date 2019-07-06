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

static int	tokens_size(t_msh *msh)
{
	int		i;
	t_tok	*tmp;

	if (!msh)
		return (0);
	i = 0;
	tmp = msh->tok;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static int process_tokens_list(t_msh *msh)
{
	int		i;
	char	**tokens;
	t_tok	*tok_cur;
	t_tok	*tok_next;

	i = tokens_size(msh);
	if (!(tokens = (char**)malloc(sizeof(char*) * (i + 2))))
		cleanup(&msh, -1, "process_tokens_list");
	bzero(tokens, sizeof(char*) * (i + 1));
	i = -1;
	tok_cur = msh->tok;
	tok_next = NULL;
	while (tok_cur)
	{
		tok_next = tok_cur->next;
		tokens[++i] = ft_strdup(tok_cur->token);
		ft_memdel((void**)&(tok_cur->token));
		ft_memdel((void**)&(tok_cur));
		tok_cur = tok_next;	
	}
	msh->tokens = tokens;
	msh->tok = tok_cur;
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

void	launch_program(t_msh *msh)
{
	pid_t   pid;
	int	    status;

	check_var(msh);
	process_tokens_list(msh);
	process_expansions(msh);
	print_table(msh->tokens);
	if (!(msh->tokens) || !(msh->tokens[0]) || check_buildins(msh))
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
	clean_table(&(msh->tokens));
}
