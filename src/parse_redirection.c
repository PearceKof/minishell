/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:40:48 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/11 17:04:59 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

extern int	g_status;

static char	*get_file_name(char *s, int *i, int size, int red_pos)
{
	char	*file_name;
	char	del;
	int		j;

	file_name = ft_calloc(sizeof(char), (size + 1));
	if (!file_name)
		malloc_error();
	pass_while_char(s, i, " ");
	del = ' ';
	j = 0;
	while (s[*i] && !ft_strchr("|;()?&", s[*i]))
	{
		if (del != new_delimiter(del, s[*i]))
			del = new_delimiter(del, s[*i]);
		else
		{
			file_name[j] = s[*i];
			j++;
		}
		*i += 1;
		if (del == ' ' && ft_strchr(" <>|;()?&", s[*i]))
			break;
	}
	replace_with_space(&s, red_pos, i);
	return (file_name);
}

/*
	prends le pointeur sur s et la redirection red que l'on cherche,
	return 0 si il y a encore au moins une redirection
	return 1 si il n'y en a plus.
*/
static int	no_more_red(char *s, char red, int i)
{
	char	del;
	// int		i;

	i++;
	del = ' ';
	while (s && s[i])
	{
		// if (del == ' ' && (s[i] == '\'' || s[i] == '\"'))
		// 	del = s[i];
		// else if (del == s[i] && (s[i] == '\'' || s[i] == '\"'))
		// 	del = ' ';
		if (del != new_delimiter(del, s[i]))
			del = new_delimiter(del, s[i]);
		else if ((s[i]) == red && del == ' ')
			return (0);
		i++;
	}
	return (1);
}

static t_cmd	*open_file(t_cmd *c, char *file_name, char red_type)
{
	if (red_type == '<')
	{
		if (c->in != 0 && c->in != -1)
			close(c->in);
		c->in = open(file_name, O_RDONLY);
	}
	else if (red_type == '>')
	{
		if (c->out != 1 && c->out != -1)
			close(c->out);
		c->out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 00777);
	}
	return (c);
}

static t_cmd	*open_attempt(char red_type, char *s, int *i, t_cmd *last)
{
	char	*file_name;

	file_name = get_file_name(s, i, file_name_size(s, *i), *i);
	last = open_file(last, file_name, red_type);
	if (red_type == '<')
	{
		if (last->in == -1 && no_more_red(s, red_type, *i))
			error(NDIR, 1, file_name, NULL);
	}
	else if (red_type == '>')
	{
		if (last->out == -1 && no_more_red(s, red_type, *i))
			error(NPERM, 1, file_name, NULL);
	}
	free(file_name);
	return (last);
}

t_cmd	*redirection(t_cmd *c, char *s)
{
	t_cmd	*last;
	char	del;
	int		i;

	i = 0;
	del = ' ';
	last = get_last_cmd(c);
	while (s && s[i])
	{
		del = new_delimiter(del, s[i]);
		if ((s[i] == '<' || s[i] == '>') && del == ' ')
		{
			last = open_attempt(s[i], s, &i, last);
		}
		i++;
	}
	return (c);
}
