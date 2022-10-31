/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:28:11 by blaurent          #+#    #+#             */
/*   Updated: 2022/02/18 11:28:11 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

char	*gnl(int fd);
char	*cooler_gnl(int fd);
char	*ft_cpyline(char *file);
char	*ft_nxtline(char *file);
char	*ft_readfile(char *file, int fd);
char	*ft_joinfile(char *s1, char *s2);

#endif