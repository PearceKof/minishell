/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:07 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/11 15:12:42 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

pid_t	ft_getpid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	return (pid - 1);
}
