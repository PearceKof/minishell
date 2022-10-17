/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:53:52 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/14 12:14:42 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_c(va_list param, int *size)
{
	int	intvalue;

	intvalue = (int)va_arg(param, int);
	*size += write(1, &intvalue, 1);
}
