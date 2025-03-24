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
INC		:= -I ../../libft -I ../../include

LIBFTDIR	:= ../../libft
LIBFT		:= $(LIBFTDIR)/libft.a

SRCDIR	:=	../../src

SRC	:=	$(SRCDIR)/expansion/minishell_expansion_01.c		\
		$(SRCDIR)/expansion/minishell_expansion_02.c		\
		$(SRCDIR)/tokenization/minishell_quote_validation.c	\
		$(SRCDIR)/tokenization/minishell_quote_removal.c	\
		$(SRCDIR)/tokenization/minishell_tokenization_01.c	\
		$(SRCDIR)/tokenization/minishell_tokenization_02.c

all: minishell_test_word_lexing_01.out minishell_test_quotes_01.out 

minishell_test_quotes_01.out: minishell_test_quotes_01.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(INC) $< $(SRC) $(LIBFT) -o $@

minishell_test_word_lexing_01.out: minishell_test_word_lexing_01.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(INC) $< $(SRC) $(LIBFT) -o $@
