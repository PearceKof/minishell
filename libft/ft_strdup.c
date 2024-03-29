/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:48:44 by blaurent          #+#    #+#             */
/*   Updated: 2022/01/12 15:48:44 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*mem;
	size_t	i;

	i = 0;
	while (src[i] != '\0')
		i++;
	mem = malloc((i + 1) * sizeof(char));
	if (mem == NULL)
	{
		ft_putstr_fd("minishell: malloc failed\nexit\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (src[i] != '\0')
	{
		mem[i] = src[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
