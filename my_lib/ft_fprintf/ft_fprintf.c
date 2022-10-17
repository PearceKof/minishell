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

#include "../includes/ft_fprintf.h"

static int	ft_check_format(va_list param, const char format, int *s, int std)
{
	if (format == 'c')
		ft_fprint_c(param, s, std);
	else if (format == 's')
		ft_fprint_s(param, s, std);
	else if (format == 'p')
		ft_fprint_p(param, s, std);
	else if (format == 'd' || format == 'i')
		ft_fprint_di(param, s, std);
	else if (format == 'u')
		ft_fprint_u(param, s, std);
	else if (format == 'x')
		ft_fprint_x(param, s, "0123456789abcdef", std);
	else if (format == 'X')
		ft_fprint_x(param, s, "0123456789ABCDEF", std);
	else if (format == '%')
		*s += write(std, "%", 1);
	else
		return (0);
	return (1);
}

int	ft_fprintf(int std, const char *format, ...)
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
			if (!(ft_check_format(param, format[i], &size, std)))
				break ;
		}
		else
			size += write(std, &format[i], 1);
	}
	va_end(param);
	return (size);
}
