/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redi_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctechy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:42:53 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/04 15:42:56 by ctechy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int	g_status;

void	file_name_uts(char *s, char red, int *i)
{
	int	len;

	len = *i;
	while (s[len] != red)
	{
		s[len] = ' ';
		len--;
	}
	s[len] = ' ';
}

void	redi_utls(char del, int i, char *s)
{
	if (del == ' ' && (s[i] == '\'' || s[i] == '\"'))
		del = s[i];
	else if (del == s[i] && (s[i] == '\'' || s[i] == '\"'))
		del = ' ';
}

t_cmd	*ptr_utls(t_cmd *c)
{
	t_cmd	*ptr;

	ptr = c;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
