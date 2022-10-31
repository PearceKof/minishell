/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:19:21 by blaurent          #+#    #+#             */
/*   Updated: 2022/07/04 14:19:21 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_fprint_s(va_list param, int *size, int std)
{
	char	*charvalue;

	charvalue = (char *)va_arg(param, char *);
	if (charvalue)
		*size += ft_putstr_fd(charvalue, std);
	else
		*size += write(std, "(null)", 6);
}
