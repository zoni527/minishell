# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 17:10:47 by jvarila           #+#    #+#              #
#    Updated: 2025/03/11 17:17:01 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror
DEBUGFLAGS	:= -g

LIBFTDIR	:= ../../libft
LIBFT		:= $(LIBFTDIR)/libft.a

SRCDIR		:= ../../src
SRC		:= $(SRCDIR)/tokenization/minishell_quote_validation.c

all: minishell_test_quotes_01

minishell_test_quotes_01: $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $@.c $(SRC) $(LIBFT) -o $@
