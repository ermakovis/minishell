#include "minishell.h"

void	add_token(char **str, t_tok **tok, int *i)
{
	t_tok *new;
	t_tok *tmp;

	*i = -1;
	if (!str || !*str)
		return ;
	if (!(new = (t_tok*)malloc(sizeof(t_tok))))
		return ;
	ft_bzero(new, sizeof(t_tok));
	new->token = ft_strdup(*str);
	ft_memdel((void**)str);
	*str = ft_strnew(2048);
	if (!*tok)
	{
		*tok = new;
		return ;
	}
	tmp = *tok;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int		process_tokens(t_msh *msh)
{
	int		i;
	int		quot;
	int		ch;
	char	*str;
	t_tok	*tok;
	
	i = -1;
	quot = 0;
	tok = NULL;
	str = ft_strnew(2048);
	while((ch = ft_getchar()) >= 0) 
	{
		if (ch == 0 || (ch == '\n' && !quot))
		{
			add_token(&str, &tok, &i);
			return 1;
		}
		if (ch == ' ')
		{
			ft_printf("%d\n", i);
			str[i] ? add_token(&str, &tok, &i) : i++;
			ft_printf("%d\n", i);
		}
		else if (ch == '\'' && !quot)
		{
			while ((ch = ft_getchar()) != '\'')
				ch == 0 ? str[++i] = ch :\
				cleanup(&msh, -1, "No match for quotes\n");
		}
		else
			str[++i] = ch;
	}
}
