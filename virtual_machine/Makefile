NAME = corewar

SRC_DIR = src

OBJ_DIR = obj

LIBFT_DIR = ../libft

#FLAGS = -Wall -Wextra -Werror

INCLUDE = -I include/ -I ../libft -I SDL2-2.0.10/build/include/SDL2 -I SDL_ttf/build/include/SDL2

SDL = -L SDL2-2.0.10/build/lib -l SDL2

SDL_TTF = -L SDL_ttf/build/lib -l SDL2_ttf

SRC = main.c \
	  read.c \
	  error.c \
	  draw.c \
	  event_handler.c \
	  print_arena.c \
	  processes.c \
	  gladiatorial_fight.c \
	  lld_lldi_lfork_aff.c \
	  live_ld_st_add.c \
	  zjmp_ldi_sti_fork.c \
	  sub_and_or_xor.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIB = ../libft/libft.a

PWD = $(shell pwd)

SDL_BUILD = SDL2-2.0.10/build

FREETYPE_BUILD = freetype-2.4.9/build

SDL_TTF_BUILD = SDL_ttf/build

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(SDL_BUILD)

all: $(NAME)

$(NAME): $(LIB) $(SDL_BUILD) $(SDL_TTF_BUILD) $(OBJ)
	@echo "$(BLUE)Linking Corewar...$(NC)"
	@gcc $(FLAGS) $(LIB) $(SDL) $(SDL_TTF) -o $(NAME) $(OBJ)
	@echo "$(GREEN)Corewar is ready!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(FLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR):
	@echo "$(GREEN)Object directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIB):
	@echo "$(BLUE)Checking libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(SDL_BUILD):
	#@echo "$(BLUE)Building SDL...$(NC)"
	tar -xf SDL2-2.0.10.zip
	mkdir $(SDL_BUILD)
	CC=$(PWD)/SDL2-2.0.10/build-scripts/gcc-fat.sh
	cd $(SDL_BUILD) ; ../configure --prefix=$(PWD)/$(SDL_BUILD)
	make -C $(SDL_BUILD)
	make -C $(SDL_BUILD) install

$(SDL_TTF_BUILD): $(FREETYPE_BUILD) 
	tar -xf SDL_ttf.tar.gz
	mkdir $(SDL_TTF_BUILD)
	cd $(SDL_TTF_BUILD) ; export SDL_CONFIG="$(PWD)/$(SDL_BUILD)/sdl2-config" ; ../configure --prefix="$(PWD)/$(SDL_TTF_BUILD)" --with-freetype-prefix="$(PWD)/$(FREETYPE_BUILD)"
	make -C $(SDL_TTF_BUILD)
	make -C $(SDL_TTF_BUILD) install

$(FREETYPE_BUILD):
	tar -xf freetype-2.4.9.tar.bz2
	mkdir $(FREETYPE_BUILD)
	cd $(FREETYPE_BUILD) ; ../configure --prefix=$(PWD)/$(FREETYPE_BUILD)
	make -C $(FREETYPE_BUILD)
	make -C $(FREETYPE_BUILD) install

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)Deleting SDL, SDL_TTF, freetype...$(NC)"
	@rm -rf SDL2-2.0.10 freetype-2.4.9 SDL_ttf

fclean: clean
	@echo "$(RED)Deleting program...$(NC)"
	@rm -rf $(NAME)
	@echo "$(RED)Deleting libft...$(NC)"
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
