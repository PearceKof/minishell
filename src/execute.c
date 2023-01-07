/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:09:09 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/06 19:54:07 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	execute_cmd(char **env, char **cmd)
{
	char	*cmdpath;

	cmdpath = ft_getpaths(env, cmd[0]);
	if (!cmdpath)
	{
		error(NCMD, 127, cmd[0], NULL);
		exit(127);
	}
	if (execve(cmdpath, cmd, env) == -1)
	{
		error(PERROR, 126, cmd[0], NULL);
		exit(126);
	}
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

static void	child(t_cmd *c, t_data *d, int *pipe)
{
	if (c->in == -1)
		exit(1);
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
	if (exec_builtin(c, d))
		exit(0);
	execute_cmd(d->env, c->full_cmd);
}

static int	execute_fork(t_cmd *c, t_data *d, int *pipe)
{
	c->pid = fork();
	if (c->pid == -1)
	{
		ft_fprintf(2, "Fork failed\n");
		return (1);
	}
	if (c->pid == 0)
		child(c, d, pipe);
	else
		close_fd(c, pipe);
	return (0);
}

/*On check l'exit avant de fork sinon la fonction exit ne fonctionne pas*/
int	execute(t_cmd *c, t_data *d)
{
	int		piper[2];
	int		ret;

	if (c && c->full_cmd[0] == NULL)
	{
		ft_fprintf(2, "TEST\n");
		return (0);
	}
	ret = execute_exit(c, d);
	while (c && c->full_cmd && !ret)
	{
		if (c->next)
			if (pipe(piper))
				return (error(PERROR, 1, NULL, NULL));
		if (execute_fork(c, d, piper))
			return (1);
		waitpid(c->pid, &g_status, 0);
		g_status = WEXITSTATUS(g_status);
		c = c->next;
	}
	return (0);
}
