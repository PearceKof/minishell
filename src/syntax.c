/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:26:28 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/14 21:20:54 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static int	print_syntax_error(char c, char *s)
{
	if (s)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n", s);
	else
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", c);
	g_status = 2;
	return (1);
}

static int	check_nxt_syntax(char *s, int i)
{
	char	c;

	c = s[i];
	if (ft_strchr("<>", s[i]) && s[i + 1] == s[i] && s[i + 2] == s[i])
		return (0);
	pass_while_char(s, &i, " ");
	if (ft_strchr("<>|#=[]!;{}()?~&", s[i]))
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n",
			s[i]);
		g_status = 2;
		return (1);
	}
	if (s[i] == '\0')
	{
		g_status = 2;
		if (ft_strchr("<>", c))
			return (error(NL, 2, NULL, NULL));
		else
			ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n",
				c);
		return (1);
	}
	return (0);
}

int	is_invalid_syntax(char *s)
{
	char	del;
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (ft_strchr("&|", s[i]))
		return (print_syntax_error(s[i], NULL));
	del = ' ';
	while (s[i])
	{
		del = new_delimiter(del, s[i]);
		if (ft_strchr("|<>&", s[i]) && del == ' ')
			if (check_nxt_syntax(s, i))
				return (1);
		i++;
	}
	return (0);
}
