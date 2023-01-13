/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:57:51 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 21:41:33 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	new_delimiter(char del, const char s)
{
	if (del == ' ' && (s == '\'' || s == '\"'))
		del = s;
	else if (del == s && (s == '\'' || s == '\"'))
		del = ' ';
	return (del);
}

void	pass_while_isalnum(const char *s, int *i)
{
	*i += 1;
	while (s[*i] && ft_isalnum(s[*i]))
		*i += 1;
}

void	pass_while_char(const char *s, int *i, char *passing_char)
{
	*i += 1;
	while (s[*i] && ft_strchr(passing_char, s[*i]))
		*i += 1;
}

void	pass_until_char(const char *s, int *i, char *ending_char)
{
	*i += 1;
	while (s[*i] && !ft_strchr(ending_char, s[*i]))
		*i += 1;
}

char	*cpy_char(char *dest, int *i, const char *src, int *j)
{
	dest[*i] = src[*j];
	*i += 1;
	*j += 1;
	return (dest);
}
