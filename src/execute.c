/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:09:09 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/14 17:41:15 by blaurent         ###   ########.fr       */
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

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (access(cmd, X_OK))
			return (NULL);
		ptr = ft_strdup(cmd);
		return (ptr);
	}
	ptr = ft_getenv("PATH", env, 4);
	env_paths = ft_split(ptr, ':');
	return (checkpaths(env_paths, cmd));
}

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
static int	execute_exit(t_cmd *c, t_data *d)
{
	int		size;

	size = ft_strlen(c->full_cmd[0]);
	if (ft_strnstr(c->full_cmd[0], "exit", size) && size == 4)
	{
		ft_exit(c->full_cmd);
		return (1);
	}
		
	else if (ft_strnstr(c->full_cmd[0], "cd", size), size == 2)
	{
		ft_cd(c, d);
		return (1);
	}
		
	else if (ft_strnstr(c->full_cmd[0], "export", size) && size == 6 && c->full_cmd[1])
	{
		ft_export(c, d);
		return (1);
	}
	return (0);
}

int	execute(t_cmd *c, t_data *d)
{
	int		piper[2];
	int		ret;
	t_cmd	*ptr;
	
	ptr = c;
	ret = execute_exit(c, d);
	while (c && !ret)
	{
		if (c->next)
			if (pipe(piper))
				return (1);
		if (execute_fork(c, d, piper))
			return (1);
		c = c->next;
	}
	while (ptr && !ret)
	{
		waitpid(ptr->pid, &g_status, 0);
		g_status = WEXITSTATUS(g_status);
		// ft_fprintf(2, "[%d]\n", g_status);
		ptr = ptr->next;
	}
	return (0);
}
