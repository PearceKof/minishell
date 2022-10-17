/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:55:24 by blaurent          #+#    #+#             */
/*   Updated: 2022/01/07 12:55:24 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *chr, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (chr[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && n > 0)
	{
		if (str[i] == chr[j])
		{
			while (str[i + j] == chr[j] && (n - j) > 0)
			{
				j++;
				if (chr[j] == '\0')
					return ((char *)str + i);
			}
			j = 0;
		}
		i++;
		n--;
	}
	return (NULL);
}
