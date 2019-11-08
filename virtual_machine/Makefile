NAME = corewar

SRC_DIR = src

OBJ_DIR = obj

#FLAGS = -Wall -Wextra -Werror

INCLUDE = -I include

SRC = main.c \
	  arena.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLUE)Linking Corewar...$(NC)"
	@gcc $(FLAGS) $(INCLUDE) -o $(NAME) $(OBJ)
	@echo "$(GREEN)Corewar is ready!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(FLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR):
	@echo "$(GREEN)Object directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Deleting program...$(NC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
