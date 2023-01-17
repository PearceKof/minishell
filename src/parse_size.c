/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:11:48 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 13:06:50 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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

	if (s[(*i) + 1] == '?')
		return (status_size(i));
	if (!ft_isalnum(s[(*i) + 1]))
	{
		*i += 1;
		return (1);
	}
	varname = isolate_varname(s, *i);
	pass_while_isalnum(s, i);
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	free(varname);
	if (!ptr)
		return (0);
	value = ft_strdup(ptr);
	free(ptr);
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
	while (s[i])
	{
		if (del != new_delimiter(del, s[i]))
		{
			del = new_delimiter(del, s[i]);
			i++;
		}
		else if (s[i] == '$' && del != '\'')
			size += var_value_size(env, s, &i);
		else if (del == ' ' && is_home_char(s, i))
			size += home_size(env, &i);
		else
		{
			size++;
			i++;
		}
		if (s[i] == ' ' && del == ' ')
			break ;
	}
	return (size);
}

int	home_size(char **env, int *i)
{
	int		size;
	char	*home_value;

	*i += 1;
	home_value = get_home(env);
	if (!home_value)
		return (1);
	size = 0;
	size = ft_strlen(home_value);
	free(home_value);
	return (size);
}

int	file_name_size(const char *s, int i, char **env)
{
	int		size;
	char	del;

	del = ' ';
	size = 0;
	while (s[i] && !ft_strchr("<>|;()?", s[i]))
	{
		if (del != new_delimiter(del, s[i]))
			del = new_delimiter(del, s[i]);
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
		if (s[i] == ' ' && del == ' ')
			break ;
	}
	return (size);
}
