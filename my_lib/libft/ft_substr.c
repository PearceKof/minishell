/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:27:27 by blaurent          #+#    #+#             */
/*   Updated: 2022/01/07 16:27:27 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_mallen(char const *s, unsigned int start, size_t len)
{
	if (start >= ft_strlen(s))
		return (0);
	else if (ft_strlen(s + start) < len)
		return (ft_strlen(s + start));
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_mallen(s, start, len) + 1));
	if (!str)
		return (NULL);
	i = start;
	while (s[i] && len-- > 0 && start <= ft_strlen(s))
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
