/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:10:42 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/16 18:43:12 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*relative_path(char *cmd)
{
	char	*tmp;
	char	*path;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin(pwd, "/");
	free(pwd);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

char	*checkpaths(char **env_paths, char *cmd)
{
	char	*cmdpath;
	char	*tmp;
	int		i;

	i = 0;
	if (!env_paths)
		return (NULL);
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i], "/");
		cmdpath = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(cmdpath, X_OK))
		{
			ft_freetab(env_paths);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
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
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)) && cmd[0] == '/')
	{
		ptr = ft_strdup(cmd);
		if (!ptr)
			malloc_error();
		return (ptr);
	}
	else if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (relative_path(cmd));
	ptr = ft_getenv("PATH", env, 4);
	if (!ptr)
		return (NULL);
	env_paths = ft_split(ptr, ':');
	if (!env_paths)
		malloc_error();
	free(ptr);
	return (checkpaths(env_paths, cmd));
}
