/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:38:27 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/07 15:38:27 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_check_format(va_list param, const char format, int *size)
{
	if (format == 'c')
		ft_print_c(param, size);
	else if (format == 's')
		ft_print_s(param, size);
	else if (format == 'p')
		ft_print_p(param, size);
	else if (format == 'd' || format == 'i')
		ft_print_di(param, size);
	else if (format == 'u')
		ft_print_u(param, size);
	else if (format == 'x')
		ft_print_x(param, size, "0123456789abcdef");
	else if (format == 'X')
		ft_print_x(param, size, "0123456789ABCDEF");
	else if (format == '%')
		*size += write(1, "%", 1);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int		size;
	int		i;
	va_list	param;

	va_start(param, format);
	i = -1;
	size = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!(ft_check_format(param, format[i], &size)))
				break ;
		}
		else
			size += write(1, &format[i], 1);
	}
	va_end(param);
	return (size);
}
