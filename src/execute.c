/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:09:09 by blaurent          #+#    #+#             */
/*   Updated: 2022/11/02 16:44:07 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t	i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (access(cmd, X_OK))
			ft_error(cmd, NULL, 127);
		ptr = ft_strdup(cmd);
		return (ptr);
	}
	i = 0;
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

int	execute(char **env, t_cmd *c)
{
	pid_t	pid;

	if (exec_builtin(c))
		return (0);
	pid = fork();
	if (pid == 0)
		execute_cmd(env, c->full_cmd);
	if (pid == -1)
		ft_error("fork", NULL, 1);
	if (waitpid(pid, NULL, 0) == -1)
		return (1);
	return (0);
}
