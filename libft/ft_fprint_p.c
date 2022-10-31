/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:15:52 by blaurent          #+#    #+#             */
/*   Updated: 2022/07/04 14:15:52 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fprint_p(va_list param, int *size, int std)
{
	void	*adressvalue;

	adressvalue = (void *)va_arg(param, void *);
	*size += write(std, "0x", 2);
	*size += ft_putaddr((unsigned long long)adressvalue, std);
}
