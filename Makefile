#colors------------------------------------------------------------------------------
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
#------------------------------------------------------------------------------------
NAME	= minishell
CC		= cc
#CFLAGS	= -Wextra -Werror -Wall -lreadline -g
CFLAGS	= -Wextra -Werror -Wall -g
HEADERS = -I ./include -I ./libft
LIBFT	= ./libft/libft.a

SRC_DIR	= src/
OBJ_DIR = obj/

SRCS	=	src/minishell_main.c \
			src/expansion/minishell_expansion_01.c \
			src/expansion/minishell_expansion_02.c \
			src/tokenization/minishell_quote_validation.c \
			src/tokenization/minishell_tokenization_01.c \
			src/tokenization/minishell_tokenization_02.c \
			src/environment/minishell_environment.c \
			src/environment/minishell_list.c


OBJS    = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#----------------------------------------------------------------------------------
all: $(LIBFT) $(NAME)

$(LIBFT):
		@make -C ./libft

#$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
$(NAME): $(OBJS) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME)
		@echo "$(GREEN)Succesfully built builtin!$(DEF_COLOR)"

#$(OBJ_DIR)%.o: $(SRC_DIR)%.c
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
		@echo "$(GREEN)Compiled: $(notdir $<)$(DEF_COLOR)"

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
#		@mkdir -p $@
#----------------------------------------------------------------------------------
clean:
		@rm	-rf $(OBJ_DIR)
		@make clean -C ./libft
		@echo "$(CYAN)Object files cleaned$(DEF_COLOR)"

fclean: clean
		@rm -rf $(NAME)
		@rm	-rf	$(LIBFT)
		@echo "$(CYAN)minishell executable files cleaned$(DEF_COLOR)"

re:	fclean all
		@echo "$(GREEN)Cleaned and rebuilt everytrhing for minishell$(DEF_COLOR)"
.PHONY: all clean fclean re
