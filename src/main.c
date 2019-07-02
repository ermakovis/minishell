#include "minishell.h"

int	ft_getchar(void)
{
    int ch;

	ch = 0;
    read(0, &ch, 1);
    return (ch);
}

char	*get_command(void)
{
	int	    i;
	int	    buff_size;
	int	    ch;
	char    *cmd;

	i = 0;
	buff_size = MSH_BUFF_SIZE;
	if (!(cmd = (char*)malloc(MSH_BUFF_SIZE)))
		return (NULL);
	ft_bzero(cmd, MSH_BUFF_SIZE);
	while (1)
	{
		ch = ft_getchar();
		if (ch == EOF || ch == '\n')
		{
			cmd[i] = '\0';
			return (cmd);
		}
		cmd[i++] = ch;
		if (i == buff_size)
		{
			buff_size += MSH_BUFF_SIZE;
			if (!(ft_notrealloc(cmd, i, buff_size))) 
			{
				ft_memdel((void**)&cmd);
				return (NULL);
			}
		}
	}
}

void	launch_program(t_msh *msh)
{
	pid_t   pid;
	int	    status;
	int	    i;

	if ((pid = fork()) < 0)
	{
		ft_printf("%s: fork failed\n", msh->tokens[0]);
		return ;
	}
	if (pid == 0 && execve(msh->tokens[0], msh->tokens, msh->env) < 0)
	{
		ft_printf("%s: command not found\n", msh->tokens[0]);
		return ;
	}
	if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}

void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{

		ft_printf("\n");
		exit(1) ;
	}
}

void	display_prompt(t_msh *msh)
{
	char	*home;
	char	*pwd;
	int		home_len;

	home = parse_env("HOME=", msh->env);
	pwd = parse_env("PWD=", msh->env);
	home_len = ft_strlen(home);
	if (ft_strnequ(pwd, home, home_len))
	{
		ft_printf("~%s $: ", pwd + home_len);	
	}
	else
		ft_printf("%s $: ", pwd);
}

int	main(int argc, char **argv, char **env)
{
	t_msh   *msh;
	char    *command;

	msh	= NULL;
	command = NULL;
	while (1)
	{
		if (!(process_env(env, &msh)))
			cleanup(NULL, -1, "Failed to process env\n");
		signal(SIGINT, handle_sigint);
		display_prompt(msh);
		if (!(command = get_command()))
			cleanup(&msh, -1, "Failed to get line\n");
		if (command && !(msh->tokens = ft_strsplit(command, ' ')))
			cleanup(&msh, -1, "Failed to obtain tokkens\n"); 
		ft_memdel((void**)&command);
		launch_program(msh);
		cleanup(&msh, 1, NULL);
	}
}

