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
NAME	= builtins
CC		= cc
CFLAGS	= -Wextra -Werror -Wall -lreadline -g
HEADERS = -I ./include
LIBFT	= ./libft/libft.a

SRC_DIR	= philo/
OBJ_DIR = obj/

SRCS	=  ./builtins00.c	

OBJS    = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#----------------------------------------------------------------------------------
all: $(LIBFT) $(NAME)

$(LIBFT):
		@make -C ./libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME)
		@echo "$(GREEN)Succesfully built builtin!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $@
#----------------------------------------------------------------------------------
clean:
		@rm	-rf $(OBJ_DIR)
		@make clean -C ./libft

fclean: clean
		@rm -rf $(NAME)
		@rm	-rf	$(LIBFT)
		@echo "$(CYAN)builtin executable files cleaned$(DEF_COLOR)"

re:	fclean all
		@echo "$(GREEN)Cleaned and rebuilt everytrhing for builtin$(DEF_COLOR)"
.PHONY: all clean fclean re
