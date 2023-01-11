/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:09:09 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/10 16:03:54 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	execute_cmd(char **env, char **cmd)
{
	char	*cmdpath;

	cmdpath = ft_getpaths(env, cmd[0]);
	if (!cmdpath)
		exit(127);
	if (execve(cmdpath, cmd, env) == -1)
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

void	kill_all(t_cmd *c)
{
	while (c)
	{
		kill(c->pid, SIGINT);
		waitpid(c->pid, NULL, 0);
		c = c->next;
	}
}

char	*find_same_pid(pid_t pid, t_cmd *c)
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

/*On check l'exit avant de fork sinon la fonction exit ne fonctionne pas*/
int	execute(t_cmd *c, t_data *d)
{
	int		piper[2];
	int		ret;
	t_cmd *ptr;
	pid_t	pid;
	int state;
	int tmp;

	if (c && c->full_cmd[0] == NULL)
		return (0);
	if (!ft_strnstr(c->full_cmd[0], "./minishell", 11))
		signal(SIGINT, sigint_in_fork_handler);
	ret = execute_exit(c, d);
	ptr = c;
	while (c && c->full_cmd && !ret)
	{
		if (c->next)
			if (pipe(piper))
				return (error(PERROR, 1, NULL, NULL));
		if (execute_fork(c, d, piper))
			return (1);
		c = c->next;
	}
	c = ptr;
	while (ptr)
	{
		state = 0;
		pid = waitpid(0 , &state, WUNTRACED|WNOHANG);
		while (!pid && pid != -1)
			pid = waitpid(0 , &state, WUNTRACED|WNOHANG);
		if (WIFEXITED(state))
		{
			tmp = 0;
			g_status = WEXITSTATUS(state);
			tmp = g_status;
			if (tmp == 127)
				error(NCMD, 127, find_same_pid(pid, c), NULL);
			else if (tmp == 126)
				error(PERROR, 126, find_same_pid(pid, c), NULL);
		}
		else if (WIFSIGNALED(state))
		{
			kill_all(c);
			break ;
		}
		ptr = ptr->next;
	}
	return (0);
}
