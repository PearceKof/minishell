/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:35:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/12 17:56:11 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

char	*move_to_filename(char *s, char **env)
{
	char	del;
	int		i;
	char	*file_name;

	i = 0;
	del = ' ';
	while (s && s[i])
	{
		if (del == ' ' && (s[i] == '\'' || s[i] == '\"'))
			del = s[i];
		else if (del == s[i] && (s[i] == '\'' || s[i] == '\"'))
			del = ' ';
		if ((s[i] == '<' && s[i + 1] == '<') && del == ' ')
		{
			s[i] = ' ';
			i += 1;
			pass_while_char(s, &i, " ");
			file_name = get_file_name(s, i, file_name_size(s, i, env), env);
		}
		i++;
	}
	return (file_name);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_heredoc(t_cmd *c, char *limiter, t_data *d)
{
	char	*line;

	c->pid = fork();
	d->filename = limiter;
	if (c->pid == 0)
	{
		c->in = open(limiter, O_RDWR | O_CREAT | O_APPEND, 0777);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				write(1, "\n", 1);
				break ;
			}
			if (!ft_strcmp(line, limiter))
			{
				free(line);
				break ;
			}
			write(c->in, line, ft_strlen(line));
			write(c->in, "\n", 1);
			free(line);
		}
		exit(0);
	}
	waitpid(c->pid, &g_status, 0);
	return (0);
}



int	is_heredoc(char *input)
{
	int	hdoc_char;
	int	i;

	i = 0;
	hdoc_char = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			pass_while_char(input, &i, " ");
			if (input[i] == '\0')
			{
				error(NL, 2, NULL, NULL);
				return (-1);
			}
			hdoc_char = 1;
		}
		if (ft_isalpha(input[i]) && hdoc_char)
			return (1);
		i++;
	}
	return (0);
}