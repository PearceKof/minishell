# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 13:41:49 by blaurent          #+#    #+#              #
#    Updated: 2022/01/17 13:41:49 by blaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

FLAGS		= -Wall -Wextra -Werror

INCLUDE 	= ./includes

FILES 		= ft_atoi.c \
						ft_bzero.c \
						ft_calloc.c \
						ft_fprint_c.c \
						ft_fprint_di.c \
						ft_fprint_p.c \
						ft_fprint_s.c \
						ft_fprint_u.c \
						ft_fprint_x.c \
						ft_fprintf.c \
						ft_freetab.c \
						ft_isalnum.c \
						ft_isalpha.c \
						ft_isascii.c \
						ft_isdigit.c \
						ft_isprint.c \
						ft_itoa.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_memset.c \
						ft_print_c.c \
						ft_print_di.c \
						ft_print_p.c \
						ft_print_s.c \
						ft_print_u.c \
						ft_print_x.c \
						ft_printf.c \
						ft_putaddr.c \
						ft_putchar_fd.c \
						ft_putchar.c \
						ft_putendl_fd.c \
						ft_putnbr_base.c \
						ft_putnbr_fd.c \
						ft_putstr_fd.c \
						ft_putstr.c \
						ft_split.c \
						ft_strchr.c \
						ft_strdup.c \
						ft_striteri.c \
						ft_strjoin.c \
						ft_strlcat.c \
						ft_strlcpy.c \
						ft_strlen.c \
						ft_strmapi.c \
						ft_strncmp.c \
						ft_strnstr.c \
						ft_strrchr.c \
						ft_strtrim.c \
						ft_substr.c \
						ft_tabdup.c \
						ft_tablen.c \
						ft_tolower.c \
						ft_toupper.c \
						ft_strchr_nb.c \
						gnl.c \
						gnl_utils.c \
					
OBJ 		= $(FILES:%.c=%.o)

BOBJ 		= $(BONUSFILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar crs $(NAME) $(OBJ)

%.o: %.c
	@gcc $(FLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BOBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re