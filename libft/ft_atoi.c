/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:00:52 by blaurent          #+#    #+#             */
/*   Updated: 2022/01/19 16:00:52 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_fprintf.h"

static int	ft_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_neg(char str)
{
	if (str == '+' || str == '-')
	{
		if (str == '-')
			return (-1);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	char				neg;
	size_t				i;
	unsigned long long	value;

	neg = 1;
	i = 0;
	value = 0;
	while (ft_space(str[i]))
		i++;
	if (ft_neg(str[i]))
	{
		neg = neg * ft_neg(str[i]);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + str[i++] - '0';
		if ((value > LLONG_MAX && neg == 1) || ((value - 1)
				> LLONG_MAX && neg == -1))
		{
			ft_fprintf(2, "minishell: exit: numeric argument required\n");
			return (255);
		}
	}
	return (value * neg);
}
