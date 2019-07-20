#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <term.h>
# include <curses.h>
# include <limits.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

# define MSH_BUFF_SIZE 2048
# define MSH_CMD_BUFF 65536
# define LEFT	4479771
# define RIGHT	4414235
# define UP	4283163
# define DOWN	4348699
# define DELETE	2117294875
# define BSPACE 127

typedef	struct	    termios	t_term;
typedef struct	    stat	t_stat;

typedef struct	    s_cmd
{
    char	    *area;
    char	    *left;
    char	    *right;
    char	    *del;
    char	    *insert_mode_on;
    char	    *insert_mode_off;
}		    t_cmd;

typedef struct	    s_lch
{
    char	    **tokens;
    char	    **env;
}		    t_lch;

typedef struct	    s_rl
{
    char	    *line;
    size_t	    line_len;
    size_t	    cur_pos;
}		    t_rl;

typedef struct	    s_var
{
    char	    *name;
    char	    *value;
}		    t_var;

typedef struct	    s_bin
{
    char	    *name;
    void	    (*func)(void);
}		    t_bin;

typedef struct	    s_msh
{
    t_rl	    *rl;
    t_cmd	    *cmd;
    t_lch	    *lch;
    t_term	    *original_state;
    t_list	    *tok;
    t_list	    *var;
    t_list	    *env;
    t_list	    *bin;
    t_list	    *history;
}		    t_msh;

t_msh		    *g_msh;

/*
**  main.c
*/
void		     set_terminal_canon(void);
void		     set_terminal_raw(void);

/*
**  init.c
**  --init_msh(void);
**  --init_cmd(void);
*/
void		    init(char **env);

/*
**  init_env.c	    
*/
void		    init_env(char **env);
void		    add_var(char *name, char *value, t_list **alist);
void		    delete_var(void *content, size_t size);
void		    print_var(t_list *list);
char		    *find_var(t_list *list, char *var_name);

/*
**  init_bins.c
*/
void		    init_bins(void);
void		    delete_builtins(void *content, size_t size);

/*
**  read_line.c
*/
int		    read_line(void);
int		    get_char(long *ch);

/*
**  rl_input_manipulation.c
*/
void		    rl_print_char(char ch);
void		    rl_move_cur(long ch);
void		    rl_del_char(long ch);

/*
**  parser.c
*/
void		   parse_line(void); 
void		    delete_str(void *content, size_t size);
void		    printl_str(t_list *list);

/*
**  pr_expans.c
*/
void		    pr_expans_dsign(char **token, int *i, char **line);
void		    pr_expans_tild(char **token, int *i, char **line);
void		    pr_expans(char **token, int *i, char **line);

/*
**  pr_quotes.c
*/
void		    pr_quotes(char **token, int *i, char **line);

/*
**  launch_programm.c
*/
void		    launch_program(void);

/*
**  find_executable.c
*/
void		    find_executable(void);

/*
**  msh_small_funcs.c
*/
void		    msh_env(void);
void		    msh_exit(void);

/*
**  utils.c
*/
void		    ft_free_table(char ***table);
void		    realloc_check(char **old_ptr, size_t old_size);
void		    ft_notrealloc(char **old_ptr, size_t old_size, size_t new_size);
void		    display_prompt(void);
void		    append_str(char **str, int *i, char *new);
char		    *var_to_str(t_var *var);

/*
**  cleanup.c
*/
void		    cleanup(int exit_code, char *message);
void		    cl_rl_struct(void);
void		    cl_lch_struct(void);
#endif
