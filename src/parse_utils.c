/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:57:51 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/30 17:42:27 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

void	pass_until_char(const char *s, int *i, char *ending_char)
{
	*i += 1;
	while (s[*i] && !ft_strchr(ending_char, s[*i]))
		*i += 1;
}

char *cpy_char(char *dest, int *i, const char *src, int *j)
{
	dest[*i] = src[*j];
	*i += 1;
	*j += 1;
	return (dest);
}

int	status_size(int *i)
{
	int		size;
	char	*value;

	*i += 2;
	value = ft_itoa(g_status);
	if (!value)
		malloc_error();
	size = ft_strlen(value);
	free(value);
	return (size);
}

int	var_value_size(char **env, const char *s, int *i)
{
	char	*varname;
	char	*ptr;
	char	*value;
	int		size;

	if (s[(*i) + 1] == '\0')
	{
		*i += 1;
		return (1);
	}
	if (s[(*i) + 1] == '?')
		return (status_size(i));
	varname = isolate_varname(s, *i);
	pass_until_char(s, i, " $\'\"");
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	size = ft_strlen(varname) + 1;
	free(varname);
	if (!ptr)
		return (0);
	value = ft_strdup(ptr);
	if (!value)
		malloc_error();
	size = ft_strlen(value);
	free(value);
	return (size);
}

int	get_str_size(const char *s, char **env, char del)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	ft_fprintf(2, "strsize bgin wth |%s|", s);
	while (s[i] && s[i] != del)
	{
		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
			del = ' ';
		else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
			del = s[i];
		else if (s[i] != '$' || del == '\'')
			size++;
		if (s[i] == '$' && del != '\'')
			size += var_value_size(env, s, &i);
		else
			i++;
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
	}
	ft_fprintf(2, "getstsrsize %d\n", size);
	return (size);
}