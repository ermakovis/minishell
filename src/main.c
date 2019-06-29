#include "minishell.h"

char	ft_getchar(void)
{
	char ch;

	read(0, &ch, 1);
	return (ch);
}

void	read_line_cleanup(char *str, int exit_code, char *message)
{
	ft_memdel((void**)&str);
	exit (exit_code);
}

int		main(int argc, char **argv, char **env)
{
	char *command;
	char **tokens;

	command = NULL;
	while (1)
	{
		ft_printf("\n$>: ");
		if (get_next_line(0, &command) == -1)
			return 0;
		if (command && !(tokens = ft_strsplit(command, ' ')))
			return 0;
		ft_printf("%s\n", tokens[0]);
		ft_printf("%s\n", tokens[1]);
		execve(tokens[0], tokens, NULL);

		ft_memdel((void**)&command);
	}
}
