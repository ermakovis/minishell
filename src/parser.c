#include "minishell.h"

void	    printl_str(t_list *list)
{
    ft_printf("token %s\n", list->content);
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
    ft_lstadd_last(&(g_msh->tok), new); 
    ft_memdel((void**)token);
    *i = 0;
}

static void	pr_semicol(char **token, int *i, char **line)
{
    add_token(token, i);
    if (!(*token = ft_strnew(MSH_BUFF_SIZE)))
	cleanup(-1, "Malloc failed at pr_semicol");
    (*token)[(*i)++] = **line;
    add_token(token, i);
}


void		parse_line(void)
{
    int	    i;
    char    *line;
    char    *token;

    i = 0;
    token = NULL;
    line = g_msh->rl->line;
    while (*line)
    {
	if (!token)
	    if (!(token = ft_strnew(MSH_BUFF_SIZE)))
		cleanup(-1, "Malloc failed at parser");
	realloc_check(&token, i);
	if ((*line == '~' && !token[0]) || *line == '$')
	    pr_expans(&token, &i, &line);
	else if (*line == '\'' || *line == '\"' || *line == '\\')
	    pr_quotes(&token, &i, &line);
	else if (*line == ' ' || *line == '\t')
	    add_token(&token, &i);
	else if (*line == ';')
	    pr_semicol(&token, &i, &line);
	else  
	    token[i++] = *line;
	line++;	
    }
    add_token(&token, &i);
    ft_memdel((void**)&token);
}
