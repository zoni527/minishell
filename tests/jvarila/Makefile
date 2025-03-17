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
CFLAGS		:= -Wall -Wextra -Werror -g
DEBUGFLAGS	:= -g

LIBFTDIR	:= ../../libft
LIBFT		:= $(LIBFTDIR)/libft.a

SRCDIR		:= ../../src
SRC		:= $(SRCDIR)/tokenization/minishell_quote_validation.c	\
		   $(SRCDIR)/utils/minishell_utils_memarena.c

all: minishell_test_quotes_01.out minishell_test_word_lexing_01.out

minishell_test_quotes_01.out: minishell_test_quotes_01.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $< $(SRC) $(LIBFT) -o $@

minishell_test_word_lexing_01.out: minishell_test_word_lexing_01.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $< $(SRC) $(LIBFT) -o $@
