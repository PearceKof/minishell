/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctechy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:20:33 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/15 01:20:38 by ctechy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cmd(t_cmd *c)
{
	int	i;
	int	j;

	i = 0;
	while (c->full_cmd[i])
	{
		j = 0;
		while (c->full_cmd[i][j])
		{
			if (c->full_cmd[i][j] == '=' || !ft_isalnum(c->full_cmd[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_nb(t_cmd *c)
{
	int	check;
	int	i;
	int	j;

	i = 0;
	if (ft_isdigit(c->full_cmd[0][0]))
		return (0);
	check = 0;
	while (c->full_cmd[i])
	{
		j = 0;
		while (c->full_cmd[i][j] && c->full_cmd[i][j] != '=')
		{
			if (ft_isdigit(c->full_cmd[i][j]))
				check = 1;
			else
				check = 0;
			j++;
		}
		i++;
	}
	if (check == 1)
		return (0);
	return (1);
}

int	ft_checker(t_cmd *c)
{
	int	i;

	i = 1;
	if (!ft_check_nb(c))
	{
		error(INVID, 1, c->full_cmd[i], NULL);
		return (1);
	}
	if (!ft_check_cmd(c))
		return (0);
	return (2);
}

int	ft_extra_export(t_cmd *c, t_data *d, int *i, int *j)
{
	if ((c->full_cmd[*i][*j] == '=' && *j != 0))
	{
		export_var(c->full_cmd[*i], *j, d);
		return (1);
	}
	else
		error(INVID, 1, c->full_cmd[*i], NULL);
	return (0);
}
