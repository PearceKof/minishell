/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:04:50 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/21 18:09:17 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*realloc_and_join(char *_input, char _buf, int _size)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (_size + 1));
	if (!new)
	{
		free(_input);
		return (NULL);
	}
	i = -1;
	while (_input[++i])
		new[i] = _input[i];
	new[i] = _buf;
	free(_input);
	return (new);
}
/*
get_input alloue de la mémoire pour enregistrer l'input en lisant le stdin
jusqu'à une nouvelle ligne

return la ligne en cas de succès
return NULL en cas d'échec (échec de lecture, de malloc)
*/
char	*get_input(void)
{
	char	*input;
	char	buf;
	int		size;

	size = 0;
	buf = 0;
	input = ft_calloc(sizeof(char), 1);
	if (!input)
		return (NULL);
	while (buf != '\n')
	{
		if (read(0, &buf, 1) == -1)
		{
			free(input);
			return (NULL);
		}
		input = realloc_and_join(input, buf, ++size);
		if (!input)
			return (NULL);
	}
	input[size - 1] = '\0';
	return (input);
}