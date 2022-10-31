/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:43:13 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/07 15:43:13 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_fprintf(int std, const char *str, ...);
void	ft_fprint_c(va_list param, int *size, int std);
void	ft_fprint_di(va_list param, int *size, int std);
void	ft_fprint_p(va_list param, int *size, int std);
void	ft_fprint_s(va_list param, int *size, int std);
void	ft_fprint_u(va_list param, int *size, int std);
void	ft_fprint_x(va_list param, int *size, char *base, int std);

#endif