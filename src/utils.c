#include "minishell.h"

int	ft_getchar(void)
{
    int ch;

    ch = 0;
    read(0, &ch, 1);
    return (ch);
}

int	ft_tablesize(char **table)
{
    int	    i;

    i = 0;
    while (table[i])
	i++;
    return (i);
}

char	*parse_env(char *var, char **env)
{
	int		i;
	int		var_len;

	i = -1;
	var_len = ft_strlen(var);
	while (env[++i])
	{
		if (ft_strnequ(env[i], var, var_len))
			return(env[i] + var_len);
	}
	return (NULL);
}

void	*ft_notrealloc(void *old_ptr, int old_size, int new_size)
{
    void *new_ptr;

    new_ptr = NULL;
    if (old_ptr)
	return (NULL);
    if (!(new_ptr = malloc(sizeof(new_size))))
	return (NULL);
    ft_bzero(new_ptr, new_size);
    ft_memcpy(new_ptr, old_ptr, old_size);
    ft_memdel((void**)&old_ptr);
    return (new_ptr);
}

void	display_prompt(t_msh *msh)
{
    char	*home;
    char	*pwd;
    int		home_len;

    home = parse_env("HOME=", msh->env);
    pwd = parse_env("PWD=", msh->env);
    home_len = ft_strlen(home);
    if (ft_strnequ(pwd, home, home_len))
    {
	ft_printf("~%s $: ", pwd + home_len);	
    }
    else
	ft_printf("%s $: ", pwd);
}
