/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:43:54 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/14 16:16:58 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_del(t_data *d, char *str, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], str, ft_strlen(str)))
		{
			tmp[j] = d->env[i];
			j++;
		}
		else
			free(d->env[i]);
		i++;
	}
	tmp[j] = NULL;
}

static void	env_dup(t_data *d, t_cmd *c, int index)
{
	int		len;
	char	*str;
	char	**tmp;

	len = ft_tablen(d->env);
	tmp = malloc(sizeof(char *) * (len));
	if (!tmp)
		malloc_error();
	str = ft_strjoin(c->full_cmd[index], "=");
	if (!str)
		malloc_error();
	var_del(d, str, tmp);
	free(d->env);
	free(str);
	d->env = tmp;
}

static int	is_var_in_env(t_data *d, t_cmd *c, int index)
{
	int		ret;
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	ret = 0;
	tmp = ft_strjoin(c->full_cmd[index], "=");
	if (!tmp)
		malloc_error();
	len = ft_strlen(tmp);
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], tmp, len))
			ret = 1;
		i++;
	}
	free(tmp);
	return (ret);
}

int	ft_unset(t_cmd *c, t_data *d)
{
	int	index;

	index = 1;
	while (c->full_cmd[index])
	{
		if (is_var_in_env(d, c, index))
			env_dup(d, c, index);
		index++;
	}
	return (1);
}
