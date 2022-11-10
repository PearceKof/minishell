/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:09:09 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/10 19:02:49 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int g_status;
static char	*checkpaths(char **env_paths, char *cmd)
{
	char	*cmdpath;
	char	*tmp;
	size_t	i;

	i = 0;
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i++], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(cmdpath, X_OK))
		{
			ft_freetab(env_paths);
			return (cmdpath);
		}
		free(cmdpath);
	}
	ft_freetab(env_paths);
	return (NULL);
}

static char	*ft_getpaths(char **env, char *cmd)
{
	char	**env_paths;
	char	*ptr;

	(void)env;
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (access(cmd, X_OK))
			ft_error(cmd, NULL, 127);
		ptr = ft_strdup(cmd);
		return (ptr);
	}
	ptr = getenv("PATH");
	env_paths = ft_split(ptr, ':');
	return (checkpaths(env_paths, cmd));
}

void	execute_cmd(char **env, char **cmd)
{
	char	*cmdpath;

	cmdpath = ft_getpaths(env, cmd[0]);
	if (!cmdpath)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_freetab(cmd);
		exit(127);
	}
	if (execve(cmdpath, cmd, env) == -1)
	{
		if (cmdpath)
			free(cmdpath);
		ft_error("execve failed", cmd, 126);
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

static void	child(t_cmd *c, char **env, int *pipe)
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
	if (exec_builtin(c))
		exit(0);
	execute_cmd(env, c->full_cmd);
}

static int	execute_fork(t_cmd *c, char **env, int *pipe)
{
	c->pid = fork();
	if (c->pid == -1)
	{
		return (1);
	}
	if (c->pid == 0)
		child(c, env, pipe);
	else
		close_fd(c, pipe);
	return (0);
}

int	execute(char **env, t_cmd *c)
{
	int		piper[2];
	t_cmd	*ptr;

	ptr = c;
	while (c)
	{
		if (c->next)
			if (pipe(piper))
				return (1);
		if (execute_fork(c, env, piper))
			return (1);
		c = c->next;
	}
	while (ptr)
	{
		waitpid(ptr->pid, &g_status, 0);
		ptr = ptr->next;
	}
	
	return (0);
}
