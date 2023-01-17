/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:26:28 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/17 11:42:41 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static int	print_syntax_error(char c)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", c);
	g_status = 2;
	return (1);
}

static int	check_nxt_syntax(char *s, int i)
{
	if (ft_strchr("<>", s[i]))
	{
		if (s[i + 1] == s[i])
			return (0);
		if ((s[i] == '<' && s[i + 1] == '>')
			|| (s[i] == '>' && s[i + 1] == '<'))
			return (print_syntax_error(s[i]));
		pass_while_char(s, &i, " ");
		if (ft_strchr("<>|#=[]!;{}()?~&", s[i]))
			return (print_syntax_error(s[i]));
		return (0);
	}
	pass_while_char(s, &i, " ");
	if (ft_strchr("|#=[]!;{}()?~&", s[i]))
		return (print_syntax_error(s[i]));
	return (0);
}

static int	have_unclosed_pipe(char *input)
{
	char	del;
	int		i;

	i = 0;
	while (input[i])
		i++;
	del = ' ';
	while (i > 0)
	{
		i--;
		del = new_delimiter(del, input[i]);
		if (input[i] == '|' && del == ' ')
			return (1);
		else if (input[i] != ' ' && del == ' ')
			return (0);
	}
	return (0);
}

static int	have_unclosed_quote(char *input)
{
	char	del;
	int		i;

	i = 0;
	del = ' ';
	while (input[i])
	{
		del = new_delimiter(del, input[i]);
		i++;
	}
	if (del == ' ')
		return (0);
	return (1);
}

int	is_invalid_syntax(char *s)
{
	char	del;
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (have_unclosed_pipe(s))
		return (error(PIPEUNCLOSED, 1, NULL, NULL));
	if (have_unclosed_quote(s))
		return (error(QUOTEUNCLOSED, 1, NULL, NULL));
	if (ft_strchr("|", s[i]))
		return (print_syntax_error(s[i]));
	del = ' ';
	while (s[i])
	{
		del = new_delimiter(del, s[i]);
		if (ft_strchr("&", s[i]) && del == ' ')
			return (print_syntax_error(s[i]));
		if (ft_strchr("|<>", s[i]) && del == ' ')
			if (check_nxt_syntax(s, i))
				return (1);
		i++;
	}
	return (0);
}
