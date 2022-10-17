/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:51:00 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/09 16:54:25 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_base(long long nb, unsigned int base, char *printnb)
{
	unsigned long long	nbr;
	int					size;

	size = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		size++;
		nbr = nb * -1;
	}
	else
		nbr = nb;
	if (nbr <= (base - 1))
		size += write(1, &printnb[nbr], 1);
	else if (nbr > (base - 1))
	{
		size += ft_putnbr_base(nbr / base, base, printnb);
		size += ft_putnbr_base(nbr % base, base, printnb);
	}
	return (size);
}
