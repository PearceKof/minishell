# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 12:26:09 by blaurent          #+#    #+#              #
#    Updated: 2022/10/17 12:33:21 by blaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

FLAGS		= 

FILES		= main.c \
				my_lib/ft_printf/ft_printf.c\
				my_lib/ft_printf/ft_print_c.c \
				my_lib/ft_printf/ft_print_p.c \
				my_lib/ft_printf/ft_print_s.c \
				my_lib/ft_printf/ft_print_u.c \
				my_lib/ft_printf/ft_print_x.c \
				my_lib/ft_printf/ft_print_di.c \
				my_lib/gnl/gnl.c \
				my_lib/gnl/gnl_utils.c \
				my_lib/libft/ft_atoi.c \
						my_lib/libft/ft_bzero.c \
						my_lib/libft/ft_calloc.c \
						my_lib/libft/ft_isalnum.c \
						my_lib/libft/ft_isalpha.c \
						my_lib/libft/ft_isascii.c \
						my_lib/libft/ft_isdigit.c \
						my_lib/libft/ft_isprint.c \
						my_lib/libft/ft_itoa.c \
						my_lib/libft/ft_memchr.c \
						my_lib/libft/ft_memcmp.c \
						my_lib/libft/ft_memcpy.c \
						my_lib/libft/ft_memmove.c \
						my_lib/libft/ft_memset.c \
						my_lib/libft/ft_putaddr.c \
						my_lib/libft/ft_putchar_fd.c \
						my_lib/libft/ft_putendl_fd.c \
						my_lib/libft/ft_putnbr_base.c \
						my_lib/libft/ft_putnbr_fd.c \
						my_lib/libft/ft_putstr_fd.c \
						my_lib/libft/ft_putstr.c \
						my_lib/libft/ft_split.c \
						my_lib/libft/ft_strchr.c \
						my_lib/libft/ft_strdup.c \
						my_lib/libft/ft_striteri.c \
						my_lib/libft/ft_strjoin.c \
						my_lib/libft/ft_strlcat.c \
						my_lib/libft/ft_strlcpy.c \
						my_lib/libft/ft_strlen.c \
						my_lib/libft/ft_strmapi.c \
						my_lib/libft/ft_strncmp.c \
						my_lib/libft/ft_strnstr.c \
						my_lib/libft/ft_strrchr.c \
						my_lib/libft/ft_strtrim.c \
						my_lib/libft/ft_substr.c \
						my_lib/libft/ft_tolower.c \
						my_lib/libft/ft_toupper.c \
				
OBJ			= $(FILES:%.c=%.o)

all: $(OBJ) $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re