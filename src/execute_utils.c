/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:10:42 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/12 17:01:06 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	execute_exit(t_cmd *c, t_data *d)
{
	int		size;

	if (c->full_cmd[0] == NULL)
		return (0);
	size = ft_strlen(c->full_cmd[0]);
	if (ft_strnstr(c->full_cmd[0], "exit", size) && size == 4)
	{
		ft_exit(c->full_cmd, c, d);
		return (1);
	}
	else if (ft_strnstr(c->full_cmd[0], "cd", size) && size == 2)
	{
		if (c->next == NULL)
			ft_cd(c, d);
		return (2);
	}
	else if (ft_strnstr(c->full_cmd[0], "export", size)
		&& size == 6 && c->full_cmd[1])
	{
		ft_export(c, d);
		return (1);
	}
	else if (ft_strnstr(c->full_cmd[0], "unset", size) && size == 5)
	{
		ft_unset(c, d);
		return (1);
	}
	return (0);
}

char	*checkpaths(char **env_paths, char *cmd)
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

char	*ft_getpaths(char **env, char *cmd)
{
	char	**env_paths;
	char	*ptr;

	if (*cmd == '\0')
		return (NULL);
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (access(cmd, X_OK))
			return (NULL);
		ptr = ft_strdup(cmd);
		return (ptr);
	}
	ptr = ft_getenv("PATH", env, 4);
	env_paths = ft_split(ptr, ':');
	free(ptr);
	return (checkpaths(env_paths, cmd));
}

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
void	wait_all(t_cmd *first, t_cmd *c)
{
	pid_t	pid;
	int state;
	int tmp;

	while (c)
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
				error(NCMD, 127, find_same_pid(pid, first), NULL);
			else if (tmp == 126)
				error(PERROR, 126, find_same_pid(pid, first), NULL);
		}
		else if (WIFSIGNALED(state))
		{
			kill_all(first);
			break ;
		}
		c = c->next;
	}
}
