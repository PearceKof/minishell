/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:23:57 by root              #+#    #+#             */
/*   Updated: 2023/01/15 21:19:16 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	sigint_in_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_status = 130;
		exit (g_status);
	}
}

void	sigint_in_fork_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_status = 130;
	}
}
/*
	check si le signal est le bon et passe à la ligne
	affiche le prompt à la ligne suivante
	nettoie la ligne
	puis réaffiche le prompt
*/

void	sigint_handler(int sig)
{
	pid_t	pid;
	int		states;

	pid = waitpid(0, &states, WNOHANG);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_status = 130;
	}
	if (sig == SIGTERM)
	{
		ft_fprintf(2, "DEBUG\n");
		exit(0);
	}
}
