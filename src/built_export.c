/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:37:34 by root              #+#    #+#             */
/*   Updated: 2022/12/30 20:44:52 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check_var_env(t_data *d, char *str, int len)
// {
// 	int		i;
// 	int		check;

// 	i = 0;
// 	check = 0;
// 	while (d->env[i])
// 	{
// 		if (!ft_strncmp(d->env[i], str, len))
// 		{
// 			check = 1;
// 			return (i);
// 		}
// 		else
// 			i++;
// 	}
// 	return (check);
// }

// static void		dup_var(char *str)
// {
// 	char	*dup;
// 	int		len;
// 	int		i;
// 	i = 0;
// 	len = ft_strlen(str);
// 	while (str[len] != '=' && i < len)
// 	{
// 		i++;
// 		len--;
// 	}
// 	dup = malloc(sizeof(char *) * i);
// 	while (i > 0)
// 	{
// 		dup2[i] = str[i];
// 		i--;
// 	}
// }

int		ft_export(t_cmd *c, t_data *d)
{
	char *full;
	char *varname;
	char *value;
	int	i;
	int j;

	full = c->full_cmd[1];
	if (*full == '=' || (*full >= '0' && *full <= '9'))
		 return(error(INVID, 1, full, NULL));
	i = 0;
	while (full[i] && full[i] != '=')
		i++;
	if (full[i] != '=')
		return (0);
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
	full += j;
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
	ft_fprintf(2, "VALUE: %s\n", value);
	d->env = set_env_var(varname, value, d, ft_strlen(varname));
	return (0);
}