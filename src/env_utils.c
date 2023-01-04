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
	int	lencmp;
	int	i;

	i = 0;
	while (env[i])
	{
		lencmp = varname_size(env[i]);
		if (ft_strnstr(env[i], varname, ft_strlen(varname)) && lencmp == len)
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
