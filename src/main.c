#include "minishell.h"

void	set_terminal_raw(void)
{
    t_term  *orig;
    t_term  raw;

    if (!(orig = (t_term*)malloc(sizeof(t_term))))
	cleanup(-1, "Failed to malloc for terminal state structure");
    if (tcgetattr(0, orig) == -1)
	cleanup(-1, "Failed to save terminal original state");
    g_msh->original_state = orig;
    if (tcgetattr(0, &raw) == -1)
	cleanup(-1, "Failed to save terminal original state");
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(0, TCSANOW, &raw) == -1)
	cleanup(-1, "Failed to set terminal to raw mode");
}

void	set_terminal_canon(void)
{
    if (tcsetattr(0, TCSANOW, g_msh->original_state) == -1)
	cleanup(-1, "Failed to set terminal to raw mode");
}

static void	init_term_command(void)
{
    t_cmd   *cmd;
    size_t  size;
    char    buffer[MSH_BUFF_SIZE];

    tgetent(buffer, "screen");
    size = sizeof(t_cmd);
    if (!(cmd = (t_cmd*)malloc(size)))
	cleanup(-1, "Failed to malloc for command structure");
    ft_bzero(cmd, size);
    cmd->left = tgetstr("le", 0);
    cmd->right = tgetstr("nd", 0);
    cmd->del = tgetstr("dc", 0);
    cmd->insert_mode_on = tgetstr("im", 0); 
    cmd->insert_mode_off = tgetstr("ei", 0);
    g_msh->cmd = cmd;
}


int	main(int argc, char **argv, char **env)
{
    int	    i;
    int	    ch;

    init_msh();
    init_term_command();
    process_env(env);
    process_builtins();
    set_terminal_raw();
    //display_prompt();
    while (read_line())
    {
	ft_printf("|%s|\n", g_msh->rl->line);
    }
    set_terminal_canon();
    cleanup(0, NULL);
}

