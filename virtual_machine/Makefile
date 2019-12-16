# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgyles <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 14:20:48 by rgyles            #+#    #+#              #
#    Updated: 2019/12/15 21:17:03 by rgyles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

PROJECT_PATH = $(shell pwd)

SDL_DIR = sdl/SDL2-2.0.10

SDL_TTF_DIR = sdl/SDL_ttf

FREETYPE_DIR = sdl/freetype-2.4.9

SDL_TARGET = sdl/lib/libSDL2.dylib

SDL_TTF_TARGET = sdl/lib/libSDL2_ttf.dylib

FREETYPE_TARGET = sdl/lib/libfreetype.dylib

LIBFT_DIR = ../libft/

LIBFT = ../libft/libft.a

SDL_LIB = lib

SDL_INCLUDE = include

INCLUDE = -I include -I ../libft -I $(SDL_INCLUDE)/SDL2

LIB = -L $(SDL_LIB) -l SDL2 -l SDL2_ttf

#FLAGS = -Wall -Wextra -Werror

SRC_DIR = src

OBJ_DIR = obj

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

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(SDL_LIB) $(OBJ) $(VISUAL_OBJ)
	@echo "$(BLUE)Linking Corewar...$(NC)"
	@gcc $(FLAGS) $(LIBFT) $(LIB) -o $(NAME) $(OBJ) $(VISUAL_OBJ)
	@echo "$(GREEN)Corewar is ready!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/corewar.h | $(OBJ_DIR)
	gcc $(FLAGS) $(INCLUDE) -o $@ -c $<

$(OBJ_DIR)/main.o: include/visual.h include/project_sdl.h

$(VISUAL_OBJ): include/visual.h include/project_sdl.h

$(OBJ_DIR):
	@echo "$(GREEN)Object directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(BLUE)Checking libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(SDL_LIB): $(SDL_TARGET) $(SDL_TTF_TARGET)
	@echo "$(GREEN)SDL libraries are installed at $(SDL_LIB)!$(NC)"
	@echo "$(GREEN)SDL headers are set at $(SDL_INCLUDE)!$(NC)"
	@echo "$(RED)Deleting build directories...$(NC)"
	@rm -rf $(SDL_DIR) $(SDL_TTF_DIR) $(FREETYPE_DIR)


$(SDL_TARGET):
	@echo "$(BLUE)Extracting SDL...$(NC)"
	@tar -xf $(SDL_DIR).zip -C sdl
	@CC=$(PROJECT_PATH)/$(SDL_DIR)/build-scripts/gcc-fat.sh
	@echo "$(BLUE)Configuring SDL build...$(NC)"
	@cd $(SDL_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(SDL_DIR) \
									--disable-joystick \
									--disable-haptic \
									--disable-sensor \
									--disable-power \
									--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
									--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
									> /dev/null
	@echo "$(BLUE)Building SDL...$(NC)"
	@make -C $(SDL_DIR) > /dev/null 2>&1
	@make -C $(SDL_DIR) install > /dev/null 2>&1
	@echo "$(GREEN)SDL is ready!$(NC)"

$(SDL_TTF_TARGET): $(FREETYPE_TARGET) 
	@echo "$(BLUE)Extracting SDL_ttf...$(NC)"
	@tar -xf $(SDL_TTF_DIR).zip -C sdl
	@echo "$(BLUE)Configuring SDL_ttf build...$(NC)"
	@cd $(SDL_TTF_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(SDL_TTF_DIR) \
										--with-sdl-prefix=$(PROJECT_PATH)/$(SDL_DIR) \
										--with-freetype-prefix=$(PROJECT_PATH)/$(FREETYPE_DIR) \
										--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
										--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
										> /dev/null
	@echo "$(BLUE)Building SDL_ttf...$(NC)"
	@make -C $(SDL_TTF_DIR) > /dev/null 2>&1
	@make -C $(SDL_TTF_DIR) install > /dev/null 2>&1
	@echo "$(GREEN)SDL_ttf is ready!$(NC)"

$(FREETYPE_TARGET):
	@echo "$(BLUE)Extracting freetype...$(NC)"
	@tar -xf sdl/freetype-2.4.9.tar.bz2 -C sdl
	@echo "$(BLUE)Configuring freetype build...$(NC)"
	@cd $(FREETYPE_DIR) ; ./configure --prefix=$(PROJECT_PATH)/$(FREETYPE_DIR) \
										--includedir=$(PROJECT_PATH)/$(SDL_INCLUDE) \
										--libdir=$(PROJECT_PATH)/$(SDL_LIB) \
										> /dev/null
	@echo "$(BLUE)Building freetype...$(NC)"
	@make -C $(FREETYPE_DIR) > /dev/null 2>&1
	@make -C $(FREETYPE_DIR) install > /dev/null 2>&1
	@echo "$(GREEN)freetype is ready!$(NC)"

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Deleting program...$(NC)"
	@rm -rf $(NAME)
	@echo "$(RED)Deleting libft...$(NC)"
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)Deleting SDL, SDL_TTF, freetype libraries and header files...$(NC)"
	@rm -rf $(SDL_LIB) $(SDL_INCLUDE)/SDL2 $(SDL_INCLUDE)/ft2build.h $(SDL_INCLUDE)/freetype2

re: fclean all

.PHONY: all clean fclean re
