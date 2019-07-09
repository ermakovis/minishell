#include "minishell.h"
typedef	struct termios	t_term;

void	set_terminal_raw(void)
{
    t_term  term;

    if (tcgetattr(0, &term) == -1)
	cleanup(-1, "terminal_raw_2");
    term.c_lflag &= ~(ICANON);
    term.c_lflag &= ~(ECHO);
    if (tcsetattr(0, TCSANOW, &term) == -1)
	cleanup(-1, "Failed to set terminal to raw mode");
}

void	set_terminal_canon(void)
{
    t_term  term;

    if (tcgetattr(0, &term) == -1)
	cleanup(-1, "Failed to get terminal stats");
    term.c_lflag |= ICANON;
    term.c_lflag |= ECHO;
    if (tcsetattr(0, TCSANOW, &term) == -1)
	cleanup(-1, "Failed to set terminal to raw mode");

}

int	main(int argc, char **argv, char **env)
{
    int	    i;
    int	    ch;

    process_env(env);
    set_terminal_raw();
    i = -1;
    ft_printf("%\n", ch);
    while(++i < 10)
    {
	ch = ft_getchar();
	ft_printf("%c", ch);
    }
    ft_printf("%\n", ch);
    set_terminal_canon();
    i = -1;
    while(++i < 10)
    {
	ch = ft_getchar();
	ft_printf(" %c", ch);
    }
    ft_printf("\n");
}

//int	main(int argc, char **argv, char **env)
//{
//	signal(SIGINT, handle_sigint);
//	process_env(env);
//	process_builtins();
//	display_prompt();
//	while (process_tokens())
//	{
//		launch_program();
//		display_prompt();
//	}
//	cleanup(0, NULL);
//}

