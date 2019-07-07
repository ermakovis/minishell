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

	if(!(i = tokens_size(msh)))
		return (0);
	if (!(tokens = (char**)malloc(sizeof(char*) * (i + 1))))
		cleanup(&msh, -1, "process_tokens_list");
	bzero(tokens, sizeof(char*) * (i + 1));
	i = -1;
	while (msh->tok)
	{
		tokens[++i] = ft_strdup(msh->tok->token);
		pop_token(msh);
	}
	msh->tokens = tokens;
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
	find_executable(msh);
	process_tokens_list(msh);
	print_table(msh->tokens);
	if (!(msh->tokens) || !(msh->tokens[0]) || check_buildins(msh));
	else if ((pid = fork()) < 0)
		ft_printf("%s: fork failed\n", msh->tokens[0]);
	else if (pid == 0)
	{
		if (execve(msh->tokens[0], msh->tokens, msh->env) < 0)
			ft_printf("%s: command not found\n", msh->tokens[0]);
		exit(-1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	clean_table(&(msh->tokens));
}
