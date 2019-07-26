#include <minishell.h>

/*
**
*/

static char  *rl_tab_compare(char *paths)
{
    DIR	    *dir;
    t_dir   *entry;
    char    *line;

    line = g_msh->rl->line;
    if (!(dir = opendir(paths)))
	return (NULL);
    while (entry = readdir(dir))
    {
	if (!ft_strncmp(entry->d_name, line, ft_strlen(line)))
	{
	    closedir(dir);
	    return (entry->d_name);
	}
    }
    closedir(dir);
    return (NULL);
}

void	rl_tab(long ch)
{
    int	    i;
    char    *path_str;
    char    **paths;
    char    *ret;

    i = -1;
    ret = NULL;
    if (ch != TAB || !(path_str = find_var(g_msh->env, "PATH")))
	return ;
    if (!(paths = ft_strsplit(path_str, ':')))
	cleanup(-1, "find_executable");
    while(paths[++i])
    {	
	if (ret = rl_tab_compare(paths[i]))
	    break;
    }
    ft_printf("%s\n", ret);

    ft_free_table(&paths); 
}
