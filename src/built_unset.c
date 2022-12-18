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

int		ft_unset(t_cmd *c)
{
	char	*str;
	int		len;

	str = c->full_cmd[1];
	if (!str)
		return (0);
	len = ft_strlen(str);
	edit_envvar(str, "hello", len);
	return (1);
}