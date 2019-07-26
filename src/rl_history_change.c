#include "minishell.h"

static int	rl_calc_hight(char *line)
{
    int	    i;
    int	    ret;
    int	    line_pos;
    t_wsize wsize; 
    
    i = -1;
    ret = 0;
    line_pos = ft_strlen(find_var(g_msh->env, "PWD"));
    ioctl(0, TIOCGWINSZ, &wsize);
    while (line[++i])
    {
	line_pos++;
	if (line[i] == '\n')
	{
	    ret += line_pos / wsize.ws_col + 1;
	    line_pos = 0;
	}
    }
    ret += line_pos / wsize.ws_col;
    return (ret);
}

void	rl_history_clean(void)
{
    t_rl    *rl;
    int	    hight;

    rl = g_msh->rl;
    hight = rl_calc_hight(rl->line);
    while (hight--)
	ft_printf("%s", g_msh->cmd->up);
    ft_printf("%s%s", g_msh->cmd->cur_start, g_msh->cmd->clear_rest);
    ft_memdel((void**)&(rl->line));
    display_prompt();
}

void	rl_history_set(int  position)
{
    t_rl    *rl;
    char    *line;

    rl = g_msh->rl;
    if (position >= 0)
	line = ft_strdup(ft_lst_num(g_msh->history, position)->content);
    else if (position == -1)
    {
	if (!rl->history_orig)
	    return ;
	line = ft_strdup(rl->history_orig);
    }
    rl->cur_pos = ft_strlen(line);
    rl->line_len = rl->cur_pos;
    rl->line = ft_strnew(((rl->line_len / MSH_BUFF_SIZE) + 1) * MSH_BUFF_SIZE);
    ft_memcpy(rl->line, line, rl->line_len);
    ft_printf("%s", line);
    ft_memdel((void**)&line);
}

void	rl_history_change(int position)
{
    t_rl    *rl;

    rl = g_msh->rl;
    if (!(rl->history_orig))
	rl->history_orig = ft_strdup(rl->line);
    rl_history_clean();
    rl_history_set(position);
}
