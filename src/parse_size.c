/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:11:48 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/09 23:29:47 by blaurent         ###   ########.fr       */
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

	if (ft_strchr(" \"\'", s[*i + 1]))
	{
		*i += 1;
		return (1);
	}
	if (s[(*i) + 1] == '?')
		return (status_size(i));
	varname = isolate_varname(s, *i);
	pass_until_char(s, i, " <>$|;()?&\"\'");
	ptr = ft_getenv(varname, env, ft_strlen(varname));
	if (!ptr)
		return (0);
	free(varname);
	if (!ptr)
		malloc_error();
	value = ft_strdup(ptr);
	free(ptr);
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
	while (s[i])
	{
		ft_fprintf(2, "\nbegin loop %d :get_str_size s= |%s| del=|%c|\n", i, &s[i], del);
		if (del == s[i] && (s[i] == '\"' || s[i] == '\''))
			del = ' ';
		else if (del == ' ' && (s[i] == '\"' || s[i] == '\''))
			del = s[i];
		else if (s[i] != '$' || del == '\'')
			size++;
		if (s[i] == '$' && del != '\'')
		{
			size += var_value_size(env, s, &i);
			ft_fprintf(2, "get_str_size s= |%s| del=|%c|\n", &s[i], del);
		}
		else
			i++;
		if (del != ' ' && s[i] == del)
		{
			del = ' ';
			i++;
		}
		if (s[i] == ' ' && del == ' ')
			break;
		// ft_fprintf(2, "end of loop get_str_size s= |%s| del=|%c|\n", &s[i], del);
	}
	ft_fprintf(2, "\n\nget_str_size %d del|%c|\n\n", size, del);
	return (size);
}

int	file_name_size(const char *s, int i)
{
	int		size;
	char	del;

	i++;
	while (s[i] == ' ')
		i++;
	del = ' ';
	size = 0;
	while (s[i] && !ft_strchr("<>$|;()?&", s[i]))
	{
		if (del == ' ' &&(s[i] == '\'' || s[i] == '\"'))
			del = s[i];
		else if (del == s[i] &&(s[i] == '\'' || s[i] == '\"'))
			del = ' ';
		else
			size++;
		i++;
	}
	ft_fprintf(2, "size: %d\n", size);
	return (size);
}
