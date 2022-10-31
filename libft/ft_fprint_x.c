/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:54:04 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/11 12:26:58 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fprint_x(va_list param, int *size, char *base, int std)
{
	unsigned int	uintvalue;

	uintvalue = (unsigned int)va_arg(param, unsigned int);
	*size += ft_putnbr_base(uintvalue, 16, base, std);
}
