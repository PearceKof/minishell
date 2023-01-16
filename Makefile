# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 12:26:09 by blaurent          #+#    #+#              #
#    Updated: 2023/01/16 23:14:13 by blaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = ./src/
SRCNAMES = $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
INC = ./include/ -I /Users/$(USER)/.brew/opt/readline/include
BUILDDIR = ./build/
BUILDOBJS = $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))
LIBDIR = ./libft/
LIBFT = ./libft/libft.a
LIBINC = ./libft/includes/

# Main rule
all: $(BUILDDIR) $(LIBFT) $(NAME)

# Object dir rule
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Objects rule
$(BUILDDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) -I$(LIBINC) -I$(INC) -o $@ -c $<

# Project file rule
$(NAME): $(BUILDOBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(BUILDOBJS) $(LIBFT) -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

# Libft rule
$(LIBFT):
	make -C $(LIBDIR)

clean:
	rm -rf $(BUILDDIR)
	make -C $(LIBDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBDIR) fclean

re: fclean all

.PHONY: all fclean clean re