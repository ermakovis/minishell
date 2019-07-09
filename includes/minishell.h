#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <limits.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

//# define EOF -1
# define MSH_BUFF_SIZE 2048



typedef struct	    stat t_stat;
typedef struct	    s_bin t_bin;
typedef struct	    s_msh t_msh;

typedef struct		s_var
{
    char			*name;
    char			*value;
    struct s_var	*next;
}					t_var;

typedef struct	    s_bin
{
    char			*name;
    void			(*func)();
    struct s_bin    *next;
}					t_bin;

typedef struct		s_tok
{
    char			*token;
    struct s_tok	*next;	
}					t_tok;

typedef	struct	    s_msh
{
    char			**env;
    char			**tokens;
    t_bin			*bin;
    t_tok			*tok;
    t_var			*var;
}					t_msh;

t_msh	*g_msh;

int		    add_token(char **str, int *i);
void		    pop_token();
void		    check_var();

void		    display_prompt();
void		    launch_program();
void		    find_executable();
void		    process_builtins();
void		    process_env(char **env);
int		    process_tokens();
void		    process_tokens_quotes(char **str, int *i, int ch);
void		    process_tokens_expans(char **str, int *i, int *ch);
void		    process_tokens_expans_dsign(char **str, int *i, int *ch);
int		    ft_getchar(void);
int		    ft_tablesize(char **table);
char		    *parse_env(char *var, char **env);
void		    cleanup(int exit_code, char *message);
void		    clean_table(char ***table);
void		    clean_tokens(t_tok **tok);
void		    realloc_check(char **str, int old_size);
char		    *ft_notrealloc(char *old_ptr, int old_size, int new_size);
void		    msh_env();
void		    msh_setenv();
void		    msh_unsetenv();
void		    msh_exit();
#endif
