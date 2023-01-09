/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:35:06 by blaurent          #+#    #+#             */
/*   Updated: 2023/01/09 16:47:47 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc(char *input)
{
	int	hdoc_char;
	int	i;

	i = 0;
	hdoc_char = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			hdoc_char = 1;
		if (ft_isalpha(input[i]) && hdoc_char)
			return (1);
		i++;
	}
	return (0);
}