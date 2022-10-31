/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:43:13 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/07 15:43:13 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_print_c(va_list param, int *size);
void	ft_print_di(va_list param, int *size);
void	ft_print_p(va_list param, int *size);
void	ft_print_s(va_list param, int *size);
void	ft_print_u(va_list param, int *size);
void	ft_print_x(va_list param, int *size, char *base);

#endif