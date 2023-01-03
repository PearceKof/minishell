/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:57:51 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/03 19:56:52 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

static int	check_nxt_char(const char *s, int i)
{
	i++;
	while (s[i] == ' ')
		i++;
	if (s[i] == '<')
		return (error(OUTERR, 2, NULL, NULL));
	else if (s[i] == '>')
		return (error(INERR, 2, NULL, NULL));
	else if (s[i] == '|')
		return (error(PIPEND, 2, NULL, NULL));
	else if (s[i] == '\0')
		return (error(NL, 2, NULL, NULL));
	return (0);
}

int	is_invalid_syntax(const char *s)
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
		if (ft_strchr("|<>", s[i]) && del == ' ')
			if (check_nxt_char(s, i))
				return (1);
		i++;
	}
	return (0);
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

void	*free_tab_and_ret_null(char **tab, int size)
{
	if (tab)
	{
		while (size >= 0)
		{
			if (tab[size])
				free(tab[size]);
			size--;
		}
		free(tab);	
	}
	return (NULL);
}
