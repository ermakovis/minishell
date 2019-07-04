#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define EOF -1
# define MSH_BUFF_SIZE 1024

typedef struct	    s_bin t_bin;
typedef struct	    s_msh t_msh;

typedef struct	    s_bin
{
    char	    *name;
    void	    (*func)(t_msh*);
    struct s_bin    *next;
}		    t_bin;

typedef	struct	    s_msh
{
    char	    *command;
    char	    **env;
    char	    **tokens;
    t_bin	    *bin;
}		    t_msh;

void		    display_prompt(t_msh *msh);
void		    launch_program(t_msh *msh);
void		    process_builtins(t_msh *msh);
void		    process_env(char **env, t_msh **msh);
int		    ft_getchar(void);
int		    ft_tablesize(char **table);
char		    *parse_env(char *var, char **env);
void		    cleanup(t_msh **msh, int exit_code, char *message);
void		    clean_table(char ***table);
void		    *ft_notrealloc(void *old_ptr, int old_size, int new_size);
void		    msh_env(t_msh *msh);
void		    msh_setenv(t_msh *msh);
void		    msh_unsetenv(t_msh *msh);
void		    msh_exit(t_msh *msh);
#endif
