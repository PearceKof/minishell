/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:37:34 by root              #+#    #+#             */
/*   Updated: 2023/01/13 23:21:39 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(int i, char *full)
{
	char	*varname;
	int		j;

	varname = malloc(sizeof(char *) * (i + 1));
	if (!varname)
		malloc_error();
	varname[i] = '\0';
	j = 0;
	while (j < i)
	{
		varname[j] = full[j];
		j++;
	}
	return (varname);
}

static char	*point_value(int i, char *full)
{
	int	j;

	j = 0;
	while (j < i)
		j++;
	j++;
	full += j;
	return (full);
}

void	export_var(char *cmd, int j, t_data *d)
{
	char	*varname;
	char	*ptr;

	ptr = NULL;
	ptr = point_value(j, cmd);
	varname = get_name(j, cmd);
	d->env = set_env_var(varname, ptr, d, ft_strlen(varname));
	free(varname);
}

static int	ft_check_cmd(t_cmd *c)
{
	int	i;
	int j;

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

static int	ft_check_nb(t_cmd *c)
{
	int check;
	int	i;
	int j;

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

int	ft_export(t_cmd *c, t_data *d)
{
	int		i;
	int		j;

	i = 1;
	if (!ft_check_nb(c))
	{
		error(INVID, 1, c->full_cmd[i], NULL);
		return (1);
	}
	if (!ft_check_cmd(c))
		return (0);
	while (c->full_cmd[i])
	{
		j = 0;
		if (c->full_cmd[i][j] == '=' || !ft_isalnum(c->full_cmd[i][j]))
		{
			error(INVID, 1, c->full_cmd[i], NULL);
			i++;
			continue ;
		}
		while (c->full_cmd[i][j] && c->full_cmd[i][j] != '=')
			j++;
		if (c->full_cmd[i][j] == '=' && j != 0)
		{
			export_var(c->full_cmd[i], j, d);
			return (1);
		}
		else
			error(INVID, 1, c->full_cmd[i], NULL);
		i++;
	}
	return (1);
}
