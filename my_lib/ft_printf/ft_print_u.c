/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:54:02 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/11 12:18:35 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_u(va_list param, int *size)
{
	unsigned int	uintvalue;

	uintvalue = (unsigned int)va_arg(param, unsigned int);
	*size += ft_putnbr_base(uintvalue, 10, "0123456789");
}
