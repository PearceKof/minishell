/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:43:47 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/15 11:30:36 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putaddr(unsigned long long nbr)
{
	char	*printnb;
	size_t	size;

	size = 0;
	printnb = "0123456789abcdef";
	if (nbr <= 15)
		size += write(1, &printnb[nbr], 1);
	else if (nbr > 15)
	{
		size += ft_putaddr(nbr / 16);
		size += ft_putaddr(nbr % 16);
	}
	return (size);
}
