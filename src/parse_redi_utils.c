/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:42:53 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/06 20:38:12 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	replace_with_space(char *s, int red_pos, int *i)
{
	*i -= 1;
	while (*i >= red_pos)
	{
		s[*i] = ' ';
		*i -= 1;
	}
}
