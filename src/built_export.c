/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:37:34 by root              #+#    #+#             */
/*   Updated: 2022/12/16 15:10:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var_env(t_data *d, char *str, int len)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], str, len))
		{
			check = 1;
			return (i);
		}
		else
			i++;
	}
	return (check);
}
/*
static void		dup_var(char *str)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (str[len] != '=' && i < len)
	{
		i++;
		len--;
	}
	dup = malloc(sizeof(char *) * i);
	while (i > 0)
	{
		dup2[i] = str[i];
		i--;
	}
}
*/
int		ft_export(t_cmd *c, t_data *d)
{
	char	*str;
	char	*dup;
	int		i;
	int		len;
	int		ret;

	i = 0;
	ret = 0;
	str = c->full_cmd[1];
	len = ft_strlen(str) + 1;
	if (str[0] == '=')
		 return(error(INVID, 1, str, NULL));
	dup = malloc(sizeof(char *) * len);
	if (!dup)
		return (0);
	while (str[i] != '=' && i < len)
	{
		dup[i] = str[i];
		i++;
	}
	if (str[i] == '\0')
		return (0);
	if (dup[0] >= '0' && dup[0] <= '9')
		return(error(INVID, 1, dup, NULL));
	if (check_var_env(d, dup, i))
	{
		ret = check_var_env(d, dup, i);
		//printf("%d", ret);
		edit_envvar(d->env[ret], c->full_cmd[1], len - 1);
	}
	addvar_to_env(d, str);
	return (0);
}
