/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:37:34 by root              #+#    #+#             */
/*   Updated: 2022/12/15 23:37:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(t_cmd *c, t_data *d)
{
	char	*str;
	char	*dup;
	int		i;

	i = 0;
	str = c->full_cmd[1];
	dup = malloc(sizeof(char) * ft_strlen(str));
	/*if (!dup)
		return malloc error*/
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