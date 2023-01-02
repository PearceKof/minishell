/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:37:34 by root              #+#    #+#             */
/*   Updated: 2022/12/22 17:23:41 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_var_env(char *full)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (full[i])
		i++;
	value = malloc(sizeof(char *) * (i + 1));
	if (!value)
		malloc_error();
	value[i] = '\0';
	j = 0;
	while (j < i)
	{
		value[j] = full[j];
		j++;
	}
	return (value);
}

static char		*var_utils(int i, char *full)
{
	int		j;

	j = 0;
	while (j < i)
		j++;
	full += j;
	return (full);
}
static char		*dup_var(int i, char *full)
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

int		ft_export(t_cmd *c, t_data *d)
{
	char *full;
	char *varname;
	char *value;
	int	i;

	full = c->full_cmd[1];
	if (*full == '=' || (*full >= '0' && *full <= '9'))
		 return(error(INVID, 1, full, NULL));
	i = 0;
	while (full[i] && full[i] != '=')
		i++;
	if (full[i] != '=')
		return (0);
	varname = dup_var(i, full);
	full = var_utils(i, full);
	value = check_var_env(full);
	ft_fprintf(2, "VALUE: %s\n", value);
	d->env = set_env_var(varname, value, d, ft_strlen(varname));
	return (0);
}
