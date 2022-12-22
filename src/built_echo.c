/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:37:16 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/22 16:41:37 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
reproduit la commande echo
*/
void	ft_echo(char **full_cmd)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = 1;
	flag = 0;
	if (full_cmd[1][0] == '-' && full_cmd[1][1] == 'n' && !full_cmd[1][2])
	{
		flag = 1;
		i = 2;
	}
	while (full_cmd[i])
	{
		j = 0;
		while (full_cmd[i][j])
		{
			write(1, &full_cmd[i][j], 1);
			j++;
		}
		if (full_cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}
