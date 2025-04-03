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

SRC	:=	$(SRCDIR)/tokenization/minishell_tokenization.c			\
		$(SRCDIR)/tokenization/minishell_variable_expansion.c		\
		$(SRCDIR)/tokenization/minishell_word_splitting.c		\
		$(SRCDIR)/tokenization/minishell_quote_removal.c		\
		$(SRCDIR)/tokenization/minishell_token_classification.c		\
		$(SRCDIR)/tokenization/minishell_is_token_01.c			\
		$(SRCDIR)/tokenization/minishell_is_token_02.c			\
		$(SRCDIR)/tokenization/minishell_assign_token_indices.c		\
		$(SRCDIR)/tokenization/minishell_token_getters.c		\
		$(SRCDIR)/tokenization/minishell_token_analysis.c		\
		$(SRCDIR)/tokenization/minishell_tokenization_utils_01.c	\
		$(SRCDIR)/tokenization/minishell_quote_validation.c		\
		$(SRCDIR)/error_handling/minishell_error_logging.c		\
		$(SRCDIR)/error_handling/minishell_syntax_error.c		\
		$(SRCDIR)/utils/minishell_var_name_len.c			\
		$(SRCDIR)/terminal_behaviour/minishell_terminal_behaviour.c	\
		$(SRCDIR)/signals/minishell_signals.c				\
		$(SRCDIR)/piping/minishell_piping.c				\
		$(SRCDIR)/utils/minishell_print_debug.c

all: minishell_test_word_lexing_01.out minishell_test_quotes_01.out minishell_test_signals.out minishell_test_pipe.out

minishell_test_quotes_01.out: minishell_test_quotes_01.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(INC) $< $(SRC) $(LIBFT) -lreadline -o $@ 

minishell_test_word_lexing_01.out: minishell_test_word_lexing_01.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(INC) $< $(SRC) $(LIBFT) -lreadline -o $@

minishell_test_signals.out: minishell_test_signals.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(INC) $< $(SRC) $(LIBFT) -lreadline -o $@

minishell_test_pipe.out: minishell_test_pipe.c $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(INC) $< $(SRC) $(LIBFT) -lreadline -o $@
