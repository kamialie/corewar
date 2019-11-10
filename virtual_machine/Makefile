NAME = corewar

SRC_DIR = src

OBJ_DIR = obj

LIBFT_DIR = ../libft

#FLAGS = -Wall -Wextra -Werror

INCLUDE = -I include/ -I ../libft

SRC = main.c \
	  arena.c \
	  read.c \
	  error.c
	  print_arena.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIB = ../libft/libft.a

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@echo "$(BLUE)Linking Corewar...$(NC)"
	@gcc $(FLAGS) $(LIB) -o $(NAME) $(OBJ)
	@echo "$(GREEN)Corewar is ready!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(FLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR):
	@echo "$(GREEN)Object directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIB):
	@echo "$(BLUE)Checking libft...$(NC)"
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Deleting program...$(NC)"
	@rm -rf $(NAME)
	@echo "$(RED)Deleting libft...$(NC)"
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
