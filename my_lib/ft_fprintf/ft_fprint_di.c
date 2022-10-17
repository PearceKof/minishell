/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:15:39 by blaurent          #+#    #+#             */
/*   Updated: 2022/07/04 14:15:39 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fprintf.h"

void	ft_fprint_di(va_list param, int *size, int std)
{
	int	intvalue;

	intvalue = (int)va_arg(param, int);
	*size += ft_putnbr_base(intvalue, 10, "0123456789", std);
}
