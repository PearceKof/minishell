/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:36:15 by root              #+#    #+#             */
/*   Updated: 2023/01/17 12:31:28 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static int	check_sign(char *sign)
{
	int	i;

	i = 0;
	if (sign[i] == '-' || sign[i] == '+')
		i++;
	return (i);
}

static int	exit_check_is_all_num(char **full_cmd)
{
	int	i;

	i = check_sign(full_cmd[1]);
	while (full_cmd[1][i])
	{
		if (full_cmd[1][i] < '0' || full_cmd[1][i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **full_cmd, t_cmd *c, t_data *d)
{
	unsigned char	nbr;

	if (!full_cmd[1])
	{
		free_cmd(c);
		free_env(d);
		exit(g_status);
	}
	if (!exit_check_is_all_num(full_cmd))
	{
		error(NUMARGS, 1, "exit", NULL);
		exit(255);
	}
	if (full_cmd[2])
		return (error(TOOARGS, 1, "exit", NULL));
	nbr = (unsigned char)ft_atoi(full_cmd[1]);
	g_status = nbr;
	exit(g_status);
	return (1);
}
