/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprint_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:15:23 by blaurent          #+#    #+#             */
/*   Updated: 2022/07/04 14:15:23 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fprintf.h"

void	ft_fprint_c(va_list param, int *size, int std)
{
	int	intvalue;

	intvalue = (int)va_arg(param, int);
	*size += write(std, &intvalue, 1);
}
