/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:09:09 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/15 16:56:42 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

extern int	g_status;

static void	execute_cmd(char **env, t_cmd *c)
{
	if (!c->path)
		exit(127);
	if (execve(c->path, c->full_cmd, env) == -1)
		exit(126);
}

static void	close_fd(t_cmd *c, int *pipe)
{
	if (c->next)
	{
		close(pipe[1]);
		if (c->next->in == STDIN_FILENO)
			c->next->in = pipe[0];
	}
	if (c->in > 2)
		close(c->in);
	if (c->out > 2)
		close(c->out);
}

static void	dup_pipe_and_exec(t_cmd *c, t_data *d, int *pipe)
{
	if (c->in != STDIN_FILENO)
	{
		if (dup2(c->in, STDIN_FILENO) == -1)
			exit(1);
		close(c->in);
	}
	if (c->out != STDOUT_FILENO)
	{
		if (dup2(c->out, STDOUT_FILENO) == -1)
			exit(1);
		close(c->out);
	}
	else if (c->next)
	{
		close(pipe[0]);
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			exit(1);
	}
	if (is_builtin(c))
		exe_child_builtin(c, d);
	execute_cmd(d->env, c);
}

static int	execute_fork(t_cmd *c, t_data *d, int *pipe)
{
	c->pid = fork();
	if (c->pid == -1)
		return (error(FORKERR, 1, NULL, NULL));
	if (c->pid == 0)
	{
		if (c->in == -1 || c->out == -1)
			exit(1);
		dup_pipe_and_exec(c, d, pipe);
	}
	else
		close_fd(c, pipe);
	return (0);
}

/*On check l'exit avant de fork sinon la fonction exit ne fonctionne pas*/
int	execute(t_cmd *c, t_data *d)
{
	int		piper[2];
	int		ret;
	t_cmd	*first;

	if (c->full_cmd[0] && !ft_strnstr(c->full_cmd[0], "./minishell", 11))
		signal(SIGINT, sigint_in_fork_handler);
	ret = exe_parent_builtin(c, d);
	first = c;
	while (c && !ret)
	{
		if (c->next && (c->out != -1 || c->in != -1))
			if (pipe(piper))
				return (error(PERROR, 1, NULL, NULL));
		if (execute_fork(c, d, piper))
			return (1);
		c = c->next;
	}
	c = first;
	if (!ret)
		wait_all(c, first);
	return (0);
}
