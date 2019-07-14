#include "minishell.h"

static void	get_line_bslash(char **str, int *i)
{
    int	ch;

    ch = 0;
    if (read(0, &ch, 4) == 4)
	return ;
    ft_printf("%c", ch);
    (*str)[++(*i)] = ch;
    if (ch == '\n')
	ft_printf("bslash> ");
}

void	get_line_squote(char **str, int *i)
{
    int	ch;

    ch = 0;
    while (read(0, &ch, 4))
    {
	if (ch == 4) 
	    cleanup(-1, "\nNo match for single quote\n");
	ft_printf("%c", ch);
	(*str)[++(*i)] = ch;
	if (ch == '\n')
	    ft_printf("squote> ");
	if (ch == '\'')
	    return ;
	realloc_check(str, *i + 1);
    }
}

void	get_line_dquote(char **str, int *i)
{
    int	ch;

    ch = 0;
    while (read(0, &ch, 4) > 0)
    {
	if (ch == 4)
	    cleanup(-1, "\nNo match for double quotes\n");
	ft_printf("%c", ch);
	(*str)[++(*i)] = ch;
	if (ch == '\\')
	    get_line_bslash(str, i);
	else if (ch == '\n')
	    ft_printf("dquote> ");
	else if (ch == '\"')
	    return ;
	realloc_check(str, *i + 1);
    }
}
char	*get_line(void)
{
    int	    i;
    int	    ch;
    char    *line;

    i = -1;
    ch = 0;
    if (!(line = ft_strnew(MSH_BUFF_SIZE)))
	cleanup(-1, "failed to malloc for line line");
    while ((read(0, &ch, 4) > 0))
    {
	if (ft_isprint(ch) && ft_printf("%c", ch))
	    line[++i] = ch;
	if (ch == '\\')
	    get_line_bslash(&line, &i);
	if (ch == '\"')
	    get_line_dquote(&line, &i);
	if (ch == '\'')
	    get_line_squote(&line, &i);
	if (ch == '\n' || ch == 4)
	{
	    ft_printf("\n");
	    return (line);
	}
	realloc_check(&line, i);
    }
    return (NULL);
}
