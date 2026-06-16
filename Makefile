#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmonjard <kmonjard@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/09 20:02:32 by kmonjard          #+#    #+#              #
#    Updated: 2026/06/10 00:14:17 by kmonjard         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = miniRT
CC = cc

CUR_DIR = $(shell pwd)
CFLAGS = -Wall -Wextra -Werror -I$(CUR_DIR)/$(HEADER_DIR)

HEADER_DIR = include

HEADERS = minirt.h \
	  parsing.h \
	  scene.h \
	  util/arrays.h \
	  util/colors.h \
	  util/cylinders.h \
	  util/planes.h \
	  util/spheres.h \
	  util/strings.h

SOURCE_DIR = src

SOURCES = main.c \
	  parsing/parse_ambience.c \
	  parsing/parse_camera.c \
	  parsing/parse_color.c \
	  parsing/parse_cylinder.c \
	  parsing/parse_double.c \
	  parsing/parse_int.c \
	  parsing/parse_light.c \
	  parsing/parse_plane.c \
	  parsing/parse_sphere.c \
	  parsing/parse_vec.c \
	  parsing/parsing.c \
	  scene/scene.c \
	  util/arrays/arrays1.c \
	  util/arrays/cylinders/cylinders1.c \
	  util/arrays/planes/planes1.c \
	  util/arrays/spheres/spheres1.c \
	  util/colors/colors1.c \
	  util/strings/strings1.c

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx
MLX_REPO = https://github.com/42paris/minilibx-linux.git
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

HEADER_FILES = $(HEADERS:%=$(HEADER_DIR)/%)
SOURCE_FILES = $(SOURCES:%=$(SOURCE_DIR)/%)

BUILD_DIR = ./build
OBJECT_FILES = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

all: $(LIBFT) $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)
	@echo "[MAKE] $(MLX_DIR)/libmlx.a"
	@$(MAKE) -C $(MLX_DIR) > /dev/null

$(LIBFT):
	@echo "[MAKE]: $(LIBFT_DIR)"
	@make -C $(LIBFT_DIR) bonus

$(NAME): $(OBJECT_FILES)
	@$(CC) $(CFLAGS) $(OBJECT_FILES) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "[COMPILE]: $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR) $(MLX_FLAGS)

clean:
	@echo "[FCLEAN] $(LIBFT_DIR) $<"
	@make -C $(LIBFT_DIR) fclean
	@echo "[CLEAN] $(MLX_DIR) $<"
	@make -C $(MLX_DIR) clean
	@rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./$(NAME)
