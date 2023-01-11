/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:40:48 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/11 21:43:10 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

extern int	g_status;

char	*get_file_name(char *s, int *i, int size, char **env)
{
	char	*file_name;
	char	*varvalue;
	char	del;
	int		j;

	size = file_name_size(s, *i, env);
	file_name = ft_calloc(sizeof(char), (size + 1));
	if (!file_name)
		malloc_error();
	pass_while_char(s, i, " ");
	del = ' ';
	j = 0;
	// file_name = cpy_file_name
	while (s[*i] && !ft_strchr("|;()?&", s[*i]))
	{
		if (del != new_delimiter(del, s[*i]))
			del = new_delimiter(del, s[*i]);
		else if (s[*i] == '$' && ft_isalnum(s[*i + 1]) && del != '\'')
		{
			varvalue = get_var_value(s, i, env);
			file_name = join_varvalue(file_name, &j, varvalue);
			free(varvalue);
		}
		else
		{
			file_name[j] = s[*i];
			j++;
		}
		*i += 1;
		if (del == ' ' && ft_strchr(" <>|;()?&", s[*i]))
			break;
	}
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

t_cmd	*redirection(t_cmd *c, t_cmd *last, char *s, char **env)
{
	char	*file_name;
	char	del;
	char	red_type;
	int		red_pos;
	int		i;

	i = 0;
	del = ' ';
	last = get_last_cmd(c);
	while (s && s[i])
	{
		del = new_delimiter(del, s[i]);
		if ((s[i] == '<' || s[i] == '>') && del == ' ')
		{
			red_type = s[i];
			red_pos = i;
			file_name = get_file_name(s, &i, file_name_size(s, i, env), env);
			replace_with_space(&s, red_pos, &i);
			last = open_file(last, file_name, red_type);
			if (red_type == '<')
			{
				if (last->in == -1 && no_more_red(s, red_type, i))
					error(NDIR, 1, file_name, NULL);
			}
			else if (red_type == '>')
			{
				if (last->out == -1 && no_more_red(s, red_type, i))
					error(NPERM, 1, file_name, NULL);
			}
			free(file_name);
		}
		i++;
	}
	return (c);
}
