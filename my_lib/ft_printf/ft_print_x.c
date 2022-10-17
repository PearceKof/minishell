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

#include "../includes/ft_printf.h"

void	ft_print_x(va_list param, int *size, char *base)
{
	unsigned int	uintvalue;

	uintvalue = (unsigned int)va_arg(param, unsigned int);
	*size += ft_putnbr_base(uintvalue, 16, base);
}
