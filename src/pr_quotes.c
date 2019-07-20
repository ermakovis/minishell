#include "minishell.h"

void		    pr_quotes_bslash(char **token, int *i, char **line)
{
    (*line)++;
    realloc_check(token, *i);
    if (**line != '\n')
	(*token)[(*i)++] = **line;
    //(*line)++;
}

void		    pr_quotes_single(char **token, int *i, char **line)
{
    (*line)++;
    while (**line && **line != '\'')
    {
	realloc_check(token, *i);
	(*token)[(*i)++] = **line;
	(*line)++;
    }
    //(*line)++;
}

void		    pr_quotes_double(char **token, int *i, char **line)
{
    (*line)++;
    while (**line && **line != '\"')
    {
	realloc_check(token, *i);
	if (**line == '$')
	    pr_expans_dsign(token, i, line);
	else if (**line == '\\')
	    pr_quotes_bslash(token, i, line);
	else
	    (*token)[(*i)++] = **line;
	(*line)++;
    }
    //(*line)++;
}

void		    pr_quotes(char **token, int *i, char **line)
{
    //if (!(**line == '\'' || **line == '\"' || **line == '\\'))
    //	return ;
    if (**line == '\'')
	pr_quotes_single(token, i, line);
    else if (**line == '\"')
	pr_quotes_double(token, i, line);
    else if (**line == '\\')
	pr_quotes_bslash(token, i, line);
    //pr_quotes(token, i, line);
}
