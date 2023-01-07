/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctechy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:26:33 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/04 15:26:36 by ctechy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
	int	i;
	int	tmp_len;

	i = 0;
	if (len < 0)
		len = ft_strlen(varname);
	while (!ft_strchr(varname, '=') && env && env[i])
	{
		tmp_len = len;
		if (tmp_len < ft_strchr_nb(env[i], '='))
			tmp_len = ft_strchr_nb(env[i], '=');
		if (!ft_strncmp(env[i], varname, tmp_len))
			return (ft_substr(env[i], tmp_len + 1, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}
