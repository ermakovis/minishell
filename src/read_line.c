#include "minishell.h"

int	    get_char(long *ch)
{
    read(STDIN_FILENO, ch, sizeof(long));
    return (1);
}

void     init_rl(void)
{
    t_rl    *new_rl;
    size_t  size;

    size = sizeof(t_rl);
    if (!(new_rl = (t_rl*)malloc(size)))
	cleanup (-1, "Failed to malloc for rl structure\n");
    ft_bzero(new_rl, size);
    if (!(new_rl->line = ft_strnew(MSH_BUFF_SIZE)))
	cleanup (-1, "Failed to malloc for rl's new string\n");
    new_rl->history = -1;
    g_msh->rl = new_rl;
}

static int     rl_quotes_check(void)
{
    int	    i;
    int	    dquote;
    int	    squote;
    char    *line;

    i = -1;
    dquote = 0;
    squote = 0;
    line = g_msh->rl->line;
    while (line[++i])
    {
	if (line[i] == '\\' && squote == 0)
	    i++;
	else if (line[i] == '\'' && dquote == 0)
	    squote ^= 1;
	else if (line[i] == '\"' && squote == 0)
	    dquote ^= 1;
    }
    !dquote && !squote ? ft_printf("\n") : rl_print_char('\n');
    if (dquote)
	ft_printf("dquote> ");
    if (squote)
	ft_printf("squote> ");
    return (!dquote && !squote);
}

int		read_line(void)
{   
    long    ch;

    ch = 0;
    init_rl();
    while (get_char(&ch))
    {
	if ((ch == '\n' && rl_quotes_check()))
	    return ((g_msh->rl->status = 1));
	else if (ch == UP || ch == DOWN)
	    rl_history(ch);
	else if (ch == LEFT || ch == RIGHT)
	    rl_move_cur(ch);
	else if (ch == DELETE || ch == BSPACE)
	    rl_del_char(ch);
	else if (ft_isprint(ch))
	    rl_print_char(ch);
	ch = 0;
    }
}
