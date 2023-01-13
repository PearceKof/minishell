/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:55:12 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/13 21:34:50 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_line_size(const char *s, char **env)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == '$')
			size += var_value_size(env, s, &i);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

int	delimiter_size(const char *s, int i)
{
	int		size;
	char	del;

	del = ' ';
	size = 0;
	while (s[i] && !ft_strchr("<>|;()?&", s[i]))
	{
		if (del != new_delimiter(del, s[i]))
			del = new_delimiter(del, s[i]);
		else
			size++;
		i++;
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
		if (s[i] == ' ' && del == ' ')
			break;
	}
	return (size);
}

char	*get_delimiter(char *s, int i, int size)
{
	char	*delimiter;
	char	del;
	int		j;

	delimiter = malloc(sizeof(char) * (size + 1));
	if (!delimiter)
		malloc_error();
	del = ' ';
	j = 0;
	while (j < size && s[i])
	{
		if (del != new_delimiter(del, s[i]))
		{
			del = new_delimiter(del, s[i]);
			i++;
		}
		else
			delimiter = cpy_char(delimiter, &j, s, &i);
	}
	delimiter[j] = '\0';
	return (delimiter);
}
