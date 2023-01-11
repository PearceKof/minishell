/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:26:28 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/11 17:23:19 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int	check_nxt_syntax(char *s, int i)
{
	if ((s[i] == '>' || s[i] == '<')
		&& ((s[i + 1] == s[i] || s[i + 1] == '&') || !s[i + 1]))
		return (error(NL, 2, NULL, NULL));
	i++;
	while (s[i] == ' ')
		i++;
	if (ft_strchr("<>\\|#=[]!;{}()*?~&", s[i]))
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", s[i - 1]);
		return (1);
	}
	return (0);
}*/

int	is_invalid_syntax(char *s)
{
	char	del;
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '|')
		return (error(PIPEND, 2, NULL, NULL));
	del = ' ';
	while (s[i])
	{
		if (del == ' ' && (s[i] == '\'' || s[i] == '\"'))
			del = s[i];
		else if (del == s[i] && (s[i] == '\'' || s[i] == '\"'))
			del = ' ';
		/*if (ft_strchr("|<>&", s[i]) && del == ' ')
			if (check_nxt_syntax(s, i))
				return (2);*/
		i++;
	}
	return (0);
}