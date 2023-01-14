/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:26:33 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/13 22:27:06 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
/*
	prends le nom d'une variable et return sa taille au premier =
	sinon, return 0
*/

int	varname_size(char *varname)
{
	int	i;

	i = 0;
	while (varname[i])
	{
		if (varname[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
/*
	prends le nom d'une variable, l'env dans lequelle on veut la chercher
	et la longueur de varname
	return un ptr juste aprés le = (sur la valeur de la variable)
	return NULL si varname ne correspond pas à un variable de l'env
*/

char	*ft_getenv(char *varname, char **env, int len)
{
	int		i;
	int		tmp_len;
	char	*var_value;

	i = 0;
	if (len < 0)
		len = ft_strlen(varname);
	while (!ft_strchr(varname, '=') && env && env[i])
	{
		tmp_len = len;
		if (tmp_len < ft_strchr_nb(env[i], '='))
			tmp_len = ft_strchr_nb(env[i], '=');
		if (!ft_strncmp(env[i], varname, tmp_len))
		{
			var_value = ft_substr(env[i], tmp_len + 1, ft_strlen(env[i]));
			if (!var_value)
				malloc_error();
			return (var_value);
		}
		i++;
	}
	return (NULL);
}
