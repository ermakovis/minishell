#include "minishell.h"

void	    printl_str(t_list *list)
{
    if (!list)
	return;
    ft_printf("%s\n", list->content);
}

void	    delete_str(void *content, size_t size)
{
    ft_memdel(&content);
    size = 0;
}

static void	add_token(char **token, int *i)
{
    t_list   *new;
    
    if (!token || !*token || !**token)
	return;
    if (!(new = ft_lstnew(*token, ft_strlen(*token) + 1)))
	cleanup(-1, "Malloc failed at add_token");
    ft_lstadd(&(g_msh->tok), new); 
    *token = NULL;
    *i = 0;
}

void		parse_line(void)
{
    int	    i;
    char    *line;
    char    *token;

    i = 0;
    token = NULL;
    line = g_msh->rl->line;
    while (line)
    {
	if (!token)
	    if (!(token = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(-1, "Malloc failed at parser");
	realloc_check(&token, i);
	if ((*line == '~' && !token[i]) || *line == '$')
	    pr_expans(&token, &i, &line);
//	else if ((*line == '\'' || *line == '\"' || *line == '\\')
//	    pr_quotes(&token, &i, &line);
	if (!*line || *line == ' ' || *line == '\t')
	    add_token(&token, &i);
	else  
	    token[i++] = *line;
	if (!*line)
	    return;
	line++;	
    }
}


