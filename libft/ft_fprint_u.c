/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:19:11 by blaurent          #+#    #+#             */
/*   Updated: 2022/07/04 14:19:11 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fprint_u(va_list param, int *size, int std)
{
	unsigned int	uintvalue;

	uintvalue = (unsigned int)va_arg(param, unsigned int);
	*size += ft_putnbr_base(uintvalue, 10, "0123456789", std);
}
