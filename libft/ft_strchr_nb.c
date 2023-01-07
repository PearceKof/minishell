/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctechy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:49:33 by ctechy            #+#    #+#             */
/*   Updated: 2023/01/07 14:49:37 by ctechy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_nb(const char *s, int c)
{
	unsigned char	str;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	str = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == str)
			return (i);
		i++;
	}
	if (str == '\0')
		return (i);
	return (-1);
}
