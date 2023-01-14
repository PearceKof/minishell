/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 15:01:07 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 22:26:58 by blaurent         ###   ########.fr       */
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

static int	ft_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_check(const char *str, int *is_neg)
{
	int	i;

	i = 0;
	while (ft_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*is_neg = -1;
		i++;
	}
	return (i);
}

int	ft_atol(const char *str, int ret)
{
	int					i;
	int					j;
	long long			nbr;
	int					is_neg;

	is_neg = 1;
	nbr = 0;
	j = 0;
	i = ft_check(str, &is_neg);
	while (str[i] <= '9' && str[i] >= '0')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (((i == 18 && is_neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && is_neg == -1) && (str[i] == '9')))
			ret = 1;
		i++;
		j++;
	}
	return (ret);
}
