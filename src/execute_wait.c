/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:03:37 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/12 17:09:44 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static char	*find_same_pid(pid_t pid, t_cmd *c)
{
	t_cmd	*ptr;

	ptr = c;
	while (ptr)
	{
		if (ptr->pid == pid)
			return (ptr->full_cmd[0]);
		ptr = ptr->next;
	}
	return (NULL);
}

static void	kill_all(t_cmd *c)
{
	while (c)
	{
		kill(c->pid, SIGINT);
		waitpid(c->pid, NULL, 0);
		c = c->next;
	}
}

void	print_error(int	status, pid_t pid, t_cmd *first)
{
	if (status == 127)
			error(NCMD, 127, find_same_pid(pid, first), NULL);
	else if (status == 126)
		error(PERROR, 126, find_same_pid(pid, first), NULL);
}

void	wait_all(t_cmd *first, t_cmd *c)
{
	pid_t	pid;
	int		state;

	while (c)
	{
		state = 0;
		pid = waitpid(0 , &state, WUNTRACED|WNOHANG);
		while (!pid && pid != -1)
			pid = waitpid(0 , &state, WUNTRACED|WNOHANG);
		if (WIFEXITED(state))
		{
			g_status = WEXITSTATUS(state);
			print_error(g_status, pid, first);
		}
		else if (WIFSIGNALED(state))
		{
			kill_all(first);
			break ;
		}
		c = c->next;
	}
}