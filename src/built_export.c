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

int	ft_export(t_cmd *c, t_data *d)
{
	char	*str;
	char	*dup;
	int		i;
	int		len;

	i = 0;
	str = c->full_cmd[1];
	len = ft_strlen(str);
	if (str[0] == '=')
		 return(error(INVID, 1, str, NULL));
	if (!ft_strchr(str, '='))
		return (0);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	while (str[i] && str[i] != '=')
	{
		dup[i] = str[i];
		i++;
	}
	if (dup[0] >= '0' && dup[0] <= '9')
		return(error(INVID, 1, dup, NULL));
	addvar_to_env(d, str);
	return (0);
}
