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

int		ft_export(t_cmd *c, t_data *d)
{
	char	*str;
	char	*dup;
	int		i;
	int		len;

	i = 0;
	str = c->full_cmd[1];
	len = ft_strlen(str) + 1;
	if (str[0] == '=')
		 return(error(INVID, 1, str, NULL));
	dup = malloc(sizeof(char) * len);
	if (!dup)
		return (0);
	while (str[i] != '=')
	{
		dup[i] = str[i];
		i++;
	}
	if (dup[0] >= '0' && dup[0] <= '9')
		return(error(INVID, 1, dup, NULL));
	addvar_to_env(d, str);
	return (0);
}
