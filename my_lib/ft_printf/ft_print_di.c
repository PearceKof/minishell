/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:53:56 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/11 12:29:52 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_di(va_list param, int *size)
{
	int	intvalue;

	intvalue = (int)va_arg(param, int);
	*size += ft_putnbr_base(intvalue, 10, "0123456789");
}
