/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:54:08 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/11 12:29:58 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_s(va_list param, int *size)
{
	char	*charvalue;

	charvalue = (char *)va_arg(param, char *);
	if (charvalue)
		*size += ft_putstr(charvalue);
	else
		*size += write(1, "(null)", 6);
}
