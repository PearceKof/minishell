/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:29:47 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 22:18:56 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/gnl.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/ft_fprintf.h"
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>

# define SPE_CHAR " $\\|#=[]!><,;{}()*?~&+-/\"'°:¨"

enum	e_error
{
	PERROR,
	QUOTE,
	ANDEND,
	PIPEND,
	OUTERR,
	INERR,
	DSUPERR,
	DINFERR,
	NL,
	NDIR,
	NPERM,
	PIPERR,
	FORKERR,
	NCMD,
	DUPERR,
	OPT,
	INVID,
	HNOSET,
	TOOARGS,
	NUMARGS
};

typedef struct s_data
{
	char	**env;
	char	*input;
	pid_t	pid;
}	t_data;

typedef struct s_cmd
{
	int				in;
	int				out;
	pid_t			pid;
	char			**full_cmd;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;
/*
	builtins.c + built_*.c
*/
void	cd_root(t_cmd *c, t_data *d);
int		ft_cd(t_cmd *c, t_data *d);
void	ft_echo(char **full_cmd);
int		ft_env(char **env);
int		ft_exit(char **full_cmd, t_cmd *c, t_data *d);
int		ft_export(t_cmd *c, t_data *d);
int		ft_unset(t_cmd *c, t_data *d);
void	new_pwd(t_data *d);
int		ft_pwd(void);
int		ft_unset(t_cmd *c, t_data *d);
int		exec_builtin(t_cmd *cmd, t_data *d);
int		ft_env(char **env);
void	new_pwd(t_data *d);
// t_data	*ft_mini(t_data *d);
void	rl_replace_line(const char *text, int clear_undo);
/*
	create_cmdlist.c
*/
t_cmd	*get_last_cmd(t_cmd *c);
t_cmd	*create_cmdlist(char *input_split, t_cmd *c, char **env);
/*
	dup_cmd.c
*/
char	*dup_cmd(char *src);
char	**dup_fullcmd(char **tab);
/*
	env.c
*/
int		varname_size(char *varname);
char	*ft_getenv(char *varname, char **env, int len);
char	*new_envvar(char *varname, char *value);
void	addvar_to_env(t_data *d, char *addvar);
char	*edit_envvar(char *to_edit, char *value, int size);
char	**set_env_var(char *varname, char *value, t_data *d, int size);
char	**init_env(char **av, t_data *d);
/*
	error.c
*/
int		error(int errorid, int error_status, char *infoa, char *infob);
void	malloc_error(void);
/*
	execute_utils.c
*/
char	*ft_getpaths(char **env, char *cmd);
char	*checkpaths(char **env_paths, char *cmd);
void	wait_all(t_cmd *first, t_cmd *c);
/*
	execute.c
*/
void	execute_cmd(char **env, char **cmd);
int		execute(t_cmd *c, t_data *d);
int		execute_exit(t_cmd *c, t_data *d);
/*
	free.c
*/
void	*free_cmd(t_cmd *c);
void	*free_env(t_data *d);
/*
	heredoc_utils.c
*/
int		get_line_size(const char *s, char **env);
int		delimiter_size(const char *s, int i);
char	*get_delimiter(char *s, int i, int size);
/*
	heredoc.c
*/
int		is_heredoc(char *input);
t_cmd	*heredoc_attempt(char **env, char *s, int *i, t_cmd *last);
t_cmd	*ft_heredoc(t_cmd *c, char *limiter, char **env);
/*
	init.c
*/
t_cmd	*init_cmd(char *input, char **env, t_data *d);
t_data	init_term(char **av, char **envp, t_data d);
/*
	parse_cmd.c
*/
char	nxt_del(char const *s, char del, char dfdel, int *i);
char	**parse_cmd(char const *s, char **env);
/*
	parse_fill.c
*/
int		get_nxt(const char *s);
char	*fill_tab(char *tab, const char **s, char **env, int size);
/*
	parse_pipe.c
*/
char	**parse_pipe(char const *s);
/*
	parse_redirection.c
*/
void	replace_with_space(char **s, int red_pos, int *i);
t_cmd	*redirection(t_cmd *c, t_cmd *last, char *s, char **env);
char	*get_file_name(char *s, int i, int size, char **env);
/*
	parse_size.c
*/
int		status_size(int *i);
int		var_value_size(char **env, const char *s, int *i);
int		get_str_size(const char *s, char **env, char del);
int		file_name_size(const char *s, int i, char **env);
/*
	parse_utils.c
*/
char	new_delimiter(char del, const char s);
void	pass_while_isalnum(const char *s, int *i);
void	pass_while_char(const char *s, int *i, char *passing_char);
void	pass_until_char(const char *s, int *i, char *ending_char);
char	*cpy_char(char *dest, int *i, const char *src, int *j);
/*
	parse_var.c
*/
char	*get_var_value(const char *s, int *j, char **env);
char	*isolate_varname(const char *s, int start);
char	*join_varvalue(char *tab, int *k, char *varvalue);
/*
	signaux.c
*/
void	sigint_in_heredoc_handler(int sig);
void	sigint_handler(int sig);
void	sigint_in_fork_handler(int sig);
/*
	syntax.c
*/
int		is_invalid_syntax(char *s);
int		is_only_space(char *s);
/*
	utils.c
*/
pid_t	ft_getpid(void);
#endif