#include "minishell.h"

int	    get_char(long *ch)
{
    read(STDIN_FILENO, ch, sizeof(long));
    return (1);
}

void	     init_rl(void)
{
    t_rl    *new_rl;
    size_t  size;

    size = sizeof(t_rl);
    if (!(new_rl = (t_rl*)malloc(size)))
	cleanup (-1, "Failed to malloc for rl structure\n");
    ft_bzero(new_rl, size);
    if (!(new_rl->line = ft_strnew(MSH_BUFF_SIZE)))
	cleanup (-1, "Failed to malloc for rl's new string\n");
    g_msh->rl = new_rl;
}

void	    rl_print_char(char ch)
{
    t_rl    *rl;

    rl = g_msh->rl;
    ft_printf("%s", g_msh->cmd->insert_mode_on);
    ft_printf("%c", ch);
    if (rl->cur_pos != rl->line_len)
	ft_memmove(&(rl->line[rl->cur_pos + 1]), &(rl->line[rl->cur_pos]),\
		rl->line_len - rl->cur_pos);
    rl->line[rl->cur_pos] = ch;
    rl->line_len++;
    rl->cur_pos++;
    ft_printf("%s", g_msh->cmd->insert_mode_off);
}

void	    rl_move_cur(long ch)
{
    t_rl    *rl;

    rl = g_msh->rl;
    if (ch == LEFT && rl->cur_pos > 0)
    {
	ft_printf("%s", g_msh->cmd->left);
	rl->cur_pos--;
    }
    else if (ch == RIGHT && rl->cur_pos < rl->line_len)
    {
	ft_printf("%s", g_msh->cmd->right);
	rl->cur_pos++;
    }
}

void	    rl_del_char(long ch)
{
    t_rl    *rl;

    rl = g_msh->rl;
    if (ch == DELETE && rl->cur_pos < rl->line_len)
    {
	ft_memmove(&(rl->line[rl->cur_pos]), &(rl->line[rl->cur_pos + 1]),\
	    rl->line_len - rl->cur_pos);
	rl->line[rl->line_len - 1] = 0;
	rl->line_len--;
	ft_printf("%s", g_msh->cmd->del);
    }
    else if (ch == BSPACE && rl->cur_pos > 0)
    {
	ft_memmove(&(rl->line[rl->cur_pos - 1]), &(rl->line[rl->cur_pos]),\
	    rl->line_len - rl->cur_pos);
	rl->line[rl->line_len - 1] = 0;
	rl->cur_pos--;
	rl->line_len--;
	ft_printf("%s%s", g_msh->cmd->left, g_msh->cmd->del);
    }
}

int	    read_line(void)
{   
    long    ch;

    ch = 0;
    init_rl();
    while (get_char(&ch))
    {
	//ft_printf("%ld\n", ch);
	if ((ch == '\n' && ft_printf("%c", ch)))
	    return (1);
	if (ch == LEFT || ch == RIGHT)
	    rl_move_cur(ch);
	if (ch == DELETE || ch == BSPACE)
	    rl_del_char(ch);
	else if (ft_isprint(ch))
	    rl_print_char(ch);
	ch = 0;
    }
    return (0);
}
