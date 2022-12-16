/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:36:15 by root              #+#    #+#             */
/*   Updated: 2022/12/16 15:09:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

static void	range(long long nbr)
{
	while (nbr <= -256 || nbr >= 256)
	{
		if (nbr <= -256)
			nbr += 256;
		else if (nbr >= 256)
			nbr -= 256;
	}
	g_status = (nbr % 256 + 256) % 256;
}

static int  check_sign(char *sign)
{
    int i;

    i = 0;
    if (sign[i] == '-' || sign[i] == '+')
        i++;
    return (i);
}

static int	exit_check_num(char **full_cmd)
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

int	ft_exit(char **full_cmd)
{
	long long	nbr;

	nbr = ft_atoi(full_cmd[1]);
	if (!full_cmd[1])
		exit(g_status);
    if (!exit_check_num(full_cmd))
    {
        error(NUMARGS, 1, "exit", NULL);
		exit(2);
    }
	if (full_cmd[2])
		return(error(TOOARGS, 1, "exit", NULL));
	if (exit_check_num(full_cmd))
	{
		range(nbr);
		exit(g_status);
	}
	return (0);
}
