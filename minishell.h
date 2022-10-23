/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:29:47 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/23 16:54:17 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../my_lib/includes/libft.h"
# include "../my_lib/includes/gnl.h"
# include "../my_lib/includes/ft_printf.h"
# include "../my_lib/includes/ft_fprintf.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

int	g_status;

typedef struct s_data
{
	char	**env;
	char	*input;
	int		end;
	pid_t	pid;
}	t_data;

typedef struct s_cmdlist
{
	struct s_cmdlist	*prev;
	char				**full_cmd;
	char				*full_path;
	pid_t				pid;
	int					in;
	int					out;
	struct s_cmdlist	*next;
}				t_cmdlist;

void	execute_cmd(char **env, char *cmd);
int		execute(char **env, char *cmd);

char	*get_input(void);

t_data *init_term(char **envp);

int		env_size(char **env);
void	ft_error(char *where, char **freed, int ret);

#endif