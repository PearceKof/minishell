/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctechy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:43:54 by ctechy            #+#    #+#             */
/*   Updated: 2022/12/17 18:43:58 by ctechy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void	var_del(t_data *d, char *str, char **tmp)
{
	int		i;
	int		j;

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

static int	env_dup(t_data *d, t_cmd *c, int index)
{
	
	int		len;
	char	*str;
	char	**tmp;

	len = env_len(d->env);
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return (0);
	str = ft_strjoin(c->full_cmd[index], "=");
	var_del(d, str, tmp);
	free(d->env);
	d->env = tmp;
	return (1);
}

static int	check_env(t_data *d, t_cmd *c, int index)
{
	int		ret;
	int		len;
	char	*tmp;
	int		i;

	i = 0;
	ret = 0;
	tmp = ft_strjoin(c->full_cmd[index], "=");
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

int		ft_unset(t_cmd *c, t_data *d)
{
	int	index;

	index = 1;
	while (c->full_cmd[index])
	{
		if (!(check_env(d, c, index)))
			return (0);
		if (!(env_dup(d, c, index)))
			return (0);
		index++;
	}
	return (1);
}