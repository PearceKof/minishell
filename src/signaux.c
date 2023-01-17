/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:23:57 by root              #+#    #+#             */
/*   Updated: 2023/01/17 14:41:30 by blaurent         ###   ########.fr       */
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
	if (sig == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_status = 131;
	}
}

void	sigint_handler(int sig)
{
	pid_t	pid;

	pid = waitpid(0, NULL, WNOHANG);
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
}
