/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:37:16 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/15 14:34:37 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char *cmd)
{
	int	j;

	if (cmd && cmd[0] == '-' && cmd[1] != '\0' && cmd[1] == 'n')
	{
		j = 1;
		while (cmd[j] == 'n')
			j++;
		if (cmd[j] == '\0')
			return (1);
	}
	return (0);
}
/*
reproduit la commande echo
*/

void	ft_echo(char **full_cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (is_flag(full_cmd[1]))
	{
		i = 2;
		flag = 1;
	}
	while (full_cmd[i])
	{
		ft_putstr(full_cmd[i]);
		if (full_cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	exit (0);
}
