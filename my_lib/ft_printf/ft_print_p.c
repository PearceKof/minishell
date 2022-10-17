/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:53:59 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/15 12:04:39 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_p(va_list param, int *size)
{
	void	*adressvalue;

	adressvalue = (void *)va_arg(param, void *);
	*size += write(1, "0x", 2);
	*size += ft_putaddr((unsigned long long)adressvalue);
}
