#include "minishell.h"

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
