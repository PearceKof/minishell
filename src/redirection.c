/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:58:47 by blaurent          #+#    #+#             */
/*   Updated: 2022/12/06 16:13:45 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int g_status;
static int	redirect_input(char **input, t_cmd *c, size_t i, size_t j)
{
	size_t	k;
	size_t	l;

	k = i;
	l = j;
	while (input[i])
	{
		while (input[i][j])
		{
			if (input[i][j] != '\0' && input[i][j] != '<')
			{
				c->in = open(&input[i][j], O_RDONLY);
				if (c->in == -1)
					return (0);
				while (i >= k)
				{
					while (input[k][l])
						input[k][l++] = ' ';
					l = 0;
					k++;
				}
				return (0);	
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (!input[i])
	{
		ft_fprintf(2, "syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

static int	redirect_output(char **input, t_cmd *c, size_t i, size_t j)
{
	size_t	k;
	size_t	l;

	k = i;
	l = j;
	while (input[i])
	{
		while (input[i][j])
		{
			if (input[i][j] != '\0' && input[i][j] != '>')
			{
				c->out = open(&input[i][j], O_WRONLY | O_TRUNC | O_CREAT, 00777);
				while (i >= k)
				{
					while (input[k][l])
						input[k][l++] = ' ';
					l = 0;
					k++;
				}
				return (0);	
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (!input[i])
	{
		ft_fprintf(2, "syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	redirection(char **input, t_cmd *c, size_t i, size_t j)
{
	// ici faudra gérer << et >>
	if (input[i][j] == '<')
		return (redirect_input(input, c, i, j));
	if (input[i][j] == '>')
		return (redirect_output(input, c, i, j));
	return (0);
}