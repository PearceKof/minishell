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

int	ft_export(t_cmd *c, t_data *d)
{
	int		i;
	int		j;
	int		ret;

	i = 1;
	ret = ft_checker(c);
	if (ret != 2)
		return (ret);
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
		if (ft_extra_export(c, d, &i, &j))
			return (1);
		i++;
	}
	return (1);
}
