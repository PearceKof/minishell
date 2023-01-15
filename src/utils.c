/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:07 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/15 17:20:54 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

