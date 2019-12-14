# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgyles <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 14:20:48 by rgyles            #+#    #+#              #
#    Updated: 2019/12/14 17:56:45 by rgyles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC_DIR = src

OBJ_DIR = obj

LIBFT_DIR = ../libft

#FLAGS = -Wall -Wextra -Werror

INCLUDE = -I include/ -I ../libft -I sdl/sdl_build/include/SDL2 -I sdl/sdl_ttf_build/include/SDL2

SDL = -L sdl/sdl_build/lib -l SDL2

SDL_TTF = -L sdl/sdl_ttf_build/lib -l SDL2_ttf

SRC = main.c \
	  read.c \
	  error.c \
	  print_arena.c \
	  processes.c \
	  gladiatorial_fight.c \
	  lld_lldi_lfork_aff.c \
	  live_ld_st_add.c \
	  zjmp_ldi_sti_fork.c \
	  sub_and_or_xor.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

VISUAL_SRC = init_visual.c \
			 initialize_visual_arena.c \
			 draw_byte.c \
			 draw_shapes.c \
			 draw_annotations.c \
			 update_byte.c \
			 show_data.c \
			 event_handler.c

VISUAL_OBJ = $(addprefix $(OBJ_DIR)/, $(VISUAL_SRC:.c=.o))

LIB = ../libft/libft.a

PWD = $(shell pwd)

SDL_BUILD = sdl/sdl_build

FREETYPE_BUILD = sdl/freetype_build

SDL_TTF_BUILD = sdl/sdl_ttf_build

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(NAME)

$(NAME): $(LIB) $(SDL_BUILD) $(SDL_TTF_BUILD) $(OBJ) $(VISUAL_OBJ)
	@echo "$(BLUE)Linking Corewar...$(NC)"
	@gcc $(FLAGS) $(LIB) $(SDL) $(SDL_TTF) -o $(NAME) $(OBJ) $(VISUAL_OBJ)
	@echo "$(GREEN)Corewar is ready!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/corewar.h | $(OBJ_DIR)
	gcc $(FLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR)/main.o: include/visual.h

$(VISUAL_OBJ): include/visual.h

$(OBJ_DIR):
	@echo "$(GREEN)Object directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIB):
	@echo "$(BLUE)Checking libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(SDL_BUILD):
	@echo "$(BLUE)Extracting SDL...$(NC)"
	@tar -xf sdl/SDL2-2.0.10.zip -C sdl
	@mkdir $(SDL_BUILD)
	@CC=$(PWD)/sdl/SDL2-2.0.10/build-scripts/gcc-fat.sh
	@echo "$(BLUE)Configuring SDL build...$(NC)"
	@cd $(SDL_BUILD) ; ../SDL2-2.0.10/configure --prefix=$(PWD)/$(SDL_BUILD) > /dev/null
	@echo "$(BLUE)Building SDL...$(NC)"
	@make -C $(SDL_BUILD) > /dev/null 2>&1
	@make -C $(SDL_BUILD) install > /dev/null 2>&1
	@echo "$(GREEN)SDL is ready!$(NC)"

$(SDL_TTF_BUILD): $(FREETYPE_BUILD) 
	@echo "$(BLUE)Extracting SDL_ttf...$(NC)"
	@tar -xf sdl/SDL_ttf.tar.gz -C sdl
	@mkdir $(SDL_TTF_BUILD)
	@echo "$(BLUE)Configuring SDL_ttf build...$(NC)"
	@cd $(SDL_TTF_BUILD) ; export SDL_CONFIG="$(PWD)/$(SDL_BUILD)/sdl2-config" ; \
		../SDL_ttf/configure --prefix="$(PWD)/$(SDL_TTF_BUILD)" --with-freetype-prefix="$(PWD)/$(FREETYPE_BUILD)" > /dev/null
	@echo "$(BLUE)Building SDL_ttf...$(NC)"
	@make -C $(SDL_TTF_BUILD) > /dev/null 2>&1
	@make -C $(SDL_TTF_BUILD) install > /dev/null 2>&1
	@echo "$(GREEN)SDL_ttf is ready!$(NC)"

$(FREETYPE_BUILD):
	@echo "$(BLUE)Extracting freetype...$(NC)"
	@tar -xf sdl/freetype-2.4.9.tar.bz2 -C sdl
	@mkdir $(FREETYPE_BUILD)
	@echo "$(BLUE)Configuring freetype build...$(NC)"
	@cd $(FREETYPE_BUILD) ; ../freetype-2.4.9/configure --prefix=$(PWD)/$(FREETYPE_BUILD) > /dev/null
	@echo "$(BLUE)Building freetype...$(NC)"
	@make -C $(FREETYPE_BUILD) > /dev/null 2>&1
	@make -C $(FREETYPE_BUILD) install > /dev/null 2>&1
	@echo "$(GREEN)freetype is ready!$(NC)"

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)Deleting SDL, SDL_TTF, freetype...$(NC)"
	@rm -rf sdl/SDL2-2.0.10 sdl/freetype-2.4.9 sdl/SDL_ttf

fclean: clean
	@echo "$(RED)Deleting program...$(NC)"
	@rm -rf $(NAME)
	@echo "$(RED)Deleting libft...$(NC)"
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Deleting SDL, SDL_TTF, freetype builds...$(NC)"
	@rm -rf sdl/sdl_build sdl/freetype_build sdl/sdl_ttf_build

re: fclean all

test:
	@echo "smth" ; echo "that"
	@rm kk 2> /dev/null >&2

.PHONY: all clean fclean re
