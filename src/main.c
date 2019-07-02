#include "minishell.h"

int	ft_getchar(void)
{
    int ch;

    read(0, &ch, 1);
    return (ch);
}

void	*ft_notrealloc(void *old_ptr, int old_size, int new_size)
{
    void *new_ptr;

    new_ptr = NULL;
    if (old_ptr)
	return (NULL);
    if (!(new_ptr = malloc(sizeof(new_size))))
	return (NULL);
    ft_bzero(new_ptr, new_size);
    ft_memcpy(new_ptr, old_ptr, old_size);
    ft_memdel((void**)&old_ptr);
    return (new_ptr);
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

void	launch_program(t_msh *msh, char **env)
{
    pid_t   pid;
    int	    status;
    int	    i;

    if ((pid = fork()) < 0)
    {
	ft_printf("%s: fork failed\n", tokens[0]);
	return ;
    }
    if (pid == 0 && execve(tokens[0], tokens, env) < 0)
    {
	ft_printf("%s: command not found", tokens[0]);
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
	return ;
    }
}

int	main(int argc, char **argv, char **env)
{
    t_msh   *msh;
    char    *command;

    msh	= NULL;
    command = NULL;
    while (1)
    {
	ft_printf("\n$>: ");
	signal(SIGINT, handle_sigint);
	if(!(msh = (t_msh*)malloc(sizeof(t_msh))))
	    cleanup(NULL, -1, "Failed to maloc for structure");
	if (!(process_env(env, msh)))
	    cleanup(NULL, -1, "Failed to process env");
	if (!(command = get_command()))
	    cleanup(&msh, -1, "Failed to get line");
	if (!ft_strlen(command) && !(msh->tokens = ft_strsplit(command, ' ')))
	    cleanup(&msh, -1, "Failed to obtain tokkens"); 
	ft_memdel((void**)&command);
	launch_program(msh, env);
	cleanup(&msh, 1, NULL);
    }
}

