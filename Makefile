# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvarila <jvarila@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 09:49:19 by jvarila           #+#    #+#              #
#    Updated: 2025/05/07 15:18:06 by jvarila          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror
DEBUG_FLAGS	:= -g
EXTRA_FLAGS	:= -lreadline
#------------------------------------------------------------------------------#
LIBFT_DIR	:= ./libft
LIBFT		:= $(LIBFT_DIR)/libft.a
#------------------------------------------------------------------------------#
INC_DIR		:= ./include
INC_FLAGS	:= -I $(LIBFT_DIR) -I $(INC_DIR)
#------------------------------------------------------------------------------#
HEADER		:= $(INC_DIR)/minishell.h
#------------------------------------------------------------------------------#
SRC_DIR	:=	./src
OBJ_DIR	:=	./obj
#------------------------------------------------------------------------------#
SRC :=	$(SRC_DIR)/tokenization/minishell_tokenization.c		\
	$(SRC_DIR)/tokenization/minishell_variable_expansion.c		\
	$(SRC_DIR)/tokenization/minishell_expandable_characters.c	\
	$(SRC_DIR)/tokenization/minishell_word_splitting.c		\
	$(SRC_DIR)/tokenization/minishell_quote_removal.c		\
	$(SRC_DIR)/tokenization/minishell_token_classification.c	\
	$(SRC_DIR)/tokenization/minishell_is_token_01.c			\
	$(SRC_DIR)/tokenization/minishell_is_token_02.c			\
	$(SRC_DIR)/tokenization/minishell_is_token_03.c			\
	$(SRC_DIR)/tokenization/minishell_assign_token_indices.c	\
	$(SRC_DIR)/tokenization/minishell_token_getters.c		\
	$(SRC_DIR)/tokenization/minishell_token_analysis.c		\
	$(SRC_DIR)/tokenization/minishell_tokenization_utils.c		\
	$(SRC_DIR)/tokenization/minishell_quote_validation.c		\
	\
	$(SRC_DIR)/error_handling/minishell_error_handling.c		\
	$(SRC_DIR)/error_handling/minishell_error_logging.c		\
	$(SRC_DIR)/error_handling/minishell_syntax_error.c		\
	$(SRC_DIR)/error_handling/minishell_exit_value_handling.c	\
	\
	$(SRC_DIR)/signals/minishell_signals.c				\
	\
	$(SRC_DIR)/piping/minishell_piping_01.c				\
	$(SRC_DIR)/piping/minishell_piping_02.c				\
	\
	$(SRC_DIR)/redirections/minishell_redirections.c		\
	$(SRC_DIR)/redirections/minishell_redirect_input.c		\
	$(SRC_DIR)/redirections/minishell_redirect_output.c		\
	$(SRC_DIR)/redirections/minishell_redirect_heredoc.c		\
	$(SRC_DIR)/redirections/minishell_redirect_append.c		\
	\
	$(SRC_DIR)/execution/minishell_execution.c			\
	$(SRC_DIR)/execution/minishell_input_validation.c		\
	$(SRC_DIR)/execution/minishell_single_builtin.c			\
	\
	$(SRC_DIR)/environment/minishell_environment_01.c		\
	$(SRC_DIR)/environment/minishell_environment_02.c		\
	$(SRC_DIR)/environment/minishell_environment_list.c		\
	$(SRC_DIR)/environment/minishell_environment_print_alpha.c	\
	$(SRC_DIR)/environment/minishell_environment_export.c		\
	$(SRC_DIR)/environment/minishell_environment_shell.c		\
	\
	$(SRC_DIR)/builtins/minishell_builtin_cd_01.c			\
	$(SRC_DIR)/builtins/minishell_builtin_cd_02.c			\
	$(SRC_DIR)/builtins/minishell_builtin_echo.c			\
	$(SRC_DIR)/builtins/minishell_builtin_env.c			\
	$(SRC_DIR)/builtins/minishell_builtin_exit.c			\
	$(SRC_DIR)/builtins/minishell_builtin_export_01.c		\
	$(SRC_DIR)/builtins/minishell_builtin_export_02.c		\
	$(SRC_DIR)/builtins/minishell_builtin_export_03.c		\
	$(SRC_DIR)/builtins/minishell_builtin_pwd.c			\
	$(SRC_DIR)/builtins/minishell_builtin_unset.c			\
	$(SRC_DIR)/builtins/minishell_builtin_dir.c			\
	$(SRC_DIR)/builtins/minishell_builtin_handler.c			\
	\
	$(SRC_DIR)/redirections/minishell_heredoc_01.c			\
	$(SRC_DIR)/redirections/minishell_heredoc_02.c			\
	\
	$(SRC_DIR)/utils/minishell_environment_utils.c			\
	$(SRC_DIR)/utils/minishell_var_name_len.c			\
	$(SRC_DIR)/utils/minishell_cleanup_and_exiting.c		\
	$(SRC_DIR)/utils/minishell_safe_fd_management.c			\
	$(SRC_DIR)/utils/minishell_safe_pipe_management.c		\
	$(SRC_DIR)/utils/minishell_token_helpers_01.c			\
	$(SRC_DIR)/utils/minishell_token_helpers_02.c			\
	$(SRC_DIR)/utils/minishell_token_helpers_03.c			\
	$(SRC_DIR)/utils/minishell_directory_validation.c		\
	$(SRC_DIR)/utils/minishell_print_debug.c			\
	$(SRC_DIR)/utils/minishell_data_reset_01.c			\
	$(SRC_DIR)/utils/minishell_data_reset_02.c			\
	$(SRC_DIR)/utils/minishell_user_input.c				\
	\
	$(SRC_DIR)/minishell_main.c
#------------------------------------------------------------------------------#
OBJ :=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
#------------------------------------------------------------------------------#
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(INC_FLAGS) $< $(LIBFT) $(EXTRA_FLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIBFT):
	make all -C $(LIBFT_DIR)
#------------------------------------------------------------------------------#
clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all
#------------------------------------------------------------------------------#
debug: CFLAGS += $(DEBUG_FLAGS)
debug: libftdebug clean_debug all

libftdebug:
	make debug -C $(LIBFT_DIR)

clean_debug:
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
#------------------------------------------------------------------------------#
.PHONY: all clean fclean re debug libftdebug clean_debug
#------------------------------------------------------------------------------#
