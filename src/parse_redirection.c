/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:40:48 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/02 21:01:01 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

extern int g_status;

// static int	redirect_input(t_cmd *c, char *input, int i)
// {
// 	int	i;

// 	i = j;
// 	while (input[i])
// 	{
// 		if (input[i] != '\0' && input[i] != '<')
// 		{
// 			c->in = open(&input[i][j], O_RDONLY);
// 			if (c->in == -1)
// 				return (1);
// 				return (0);	
// 			}
// 			j++;
// 		}
// 		j++;
// 	}
// 	if (!input[i])
// 	{
// 		ft_fprintf(2, "syntax error near unexpected token `newline'\n");
// 		return (1);
// 	}
// 	return (0);
// }

// static int	redirect_output(t_cmd *c, char *input, int i)
// {
// 	int	i;

// 	i = j;
// 	while (input[i][j])
// 	{
// 		if (input[i][j] != '\0' && input[i][j] != '>')
// 		{
// 			c->out = open(&input[i][j], O_WRONLY | O_TRUNC | O_CREAT, 00777);
// 			while (i >= k)
// 			{
// 				while (input[k][l])
// 					input[k][l++] = 0;
// 				l = 0;
// 				k++;
// 				}
// 				return (0);	
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	if (!input[i])
// 	{
// 		ft_fprintf(2, "syntax error near unexpected token `newline'\n");
// 		return (1);
// 	}
// 	return (0);
// }

static char *get_file_name(const char *s, char red, int *i, int size)
{
	char	*file_name;
	char	del;
	int		j;
	ft_fprintf(2, "\n\nFILE_SIZE HERE %d\n\n", size);
	file_name = malloc(sizeof(char) * (size + 1));
	if (!file_name)
		malloc_error();
	*i += 1;
	while (s[*i] && s[*i] == ' ')
		*i += 1;
	del = ' ';
	if (s[*i] && (s[*i] == '\'' || s[*i] == '\"'))
	{
		del = s[*i];
		*i += 1;
	}
	j = 0;
	while (s[*i] && s[*i] != red && s[*i] != del && !ft_strchr("$\\#=[]!|;{}()*?~&+-", s[*i]))
		file_name = cpy_char(file_name , &j, s, i);
	file_name[j] = '\0';
	return (file_name);
}

static int	file_name_size(const char *s, char red, int i)
{
	int		size;
	char	del;

	i++;
	while (s[i] && s[i] == ' ')
		i++;
	del = ' ';
	if (s[i] && (s[i] == '\'' || s[i] == '\"'))
	{
		del = s[i];
		i++;
	}
	size = 0;
	while (s[i] && s[i] != red && s[i] != del && !ft_strchr("$\\#=[]!|;{}()*?~&+-", s[i]))
	{
		size++;
		i++;
	}
	// ft_fprintf(2, "\n\nFILE_SIZE HERE %d\n\n", size);
	return (size);
}

t_cmd	*redirection(t_cmd *c, const char *s)
{
	int		i;
	char	*file_name;

	file_name = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			file_name = get_file_name(s, s[i], &i, file_name_size(s, s[i], i));
			ft_fprintf(2, "\n\nFILE_NAME HERE %s\n\n", file_name);
		}
		i++;
	}
	// if (s[i] == '<')
	// 	return (redirect_input(c, s, i));
	// if (s[i] == '>')
	// 	return (redirect_output(c, s, i));
	return (c);
}