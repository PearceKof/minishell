/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:29:47 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/22 15:03:01 by blaurent         ###   ########.fr       */
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

typedef struct s_term
{
	char	**env;
}	t_term;

void	execute_cmd(char **env, char *cmd);
int		execute(char **env, char *cmd);

char	*get_input(void);

t_term	*init_term(char **envp);

int		env_size(char **env);
void	ft_error(char *where, char **freed, int ret);

#endif