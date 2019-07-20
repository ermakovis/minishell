#include "minishell.h"

void	ft_free_table(char ***table)
{
    char    **tmp;
    int	    i;

    if (!table || !*table)
	return ;
    i = -1;
    tmp = *table;
    while (tmp[++i])
	ft_memdel((void**)&tmp[i]);
    ft_memdel((void**)table);
}

void realloc_check(char **old_ptr, size_t old_size)
{
    size_t  new_size;
    char    *new_str;

    if (!old_ptr || !*old_ptr || !**old_ptr || old_size % MSH_BUFF_SIZE != 0)
	return ;
    new_size = ((old_size / MSH_BUFF_SIZE) + 1) * MSH_BUFF_SIZE;
    ft_notrealloc(old_ptr, old_size, new_size);
}

void	ft_notrealloc(char **old_ptr, size_t old_size, size_t new_size)
{
    char    *new_ptr;

    if (!old_ptr || !*old_ptr)
	return ;
    if (!(new_ptr = ft_strnew(new_size)))
	cleanup(-1, "Failed to realloc");
    ft_memcpy(new_ptr, *old_ptr, old_size);
    ft_memdel((void**)old_ptr);
    *old_ptr = new_ptr;
}

char	*var_to_str(t_var *var)
{
    char    *ret;
    size_t  name_len;
    size_t  val_len;

    name_len = ft_strlen(var->name);
    val_len = ft_strlen(var->value);
    if (!(ret = (char*)malloc(name_len + val_len + 2)))
	cleanup (-1, "Malloc failed at var_to_srt");
    ft_bzero(ret, name_len + val_len + 2);
    ft_memcpy(ret, var->name, name_len);
    ret[name_len] = '=';
    ft_memcpy(ret, var->value, val_len);
    return (ret);
}

void	append_str(char **str, int *i, char *new)
{
    int	    j;

    if (!new || !*new || !i || !new)
	return ;
    j = -1;
    while (new[++j])
    {
	realloc_check(str, *i + 1);
	(*str)[(*i)++] = new[j];
    }
}

void	display_prompt(void)
{
    char	*home;
    char	*pwd;
    int		home_len;

    if (!isatty(0))
	return ;
    home = find_var(g_msh->env, "HOME");
    pwd = find_var(g_msh->env, "PWD");
    home_len = ft_strlen(home);
    if (ft_strnequ(pwd, home, home_len))
    {
	ft_printf("~%s $: ", pwd + home_len);	
    }
    else
	ft_printf("%s $: ", pwd);
}
