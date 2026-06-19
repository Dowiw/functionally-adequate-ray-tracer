# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/09 20:02:32 by kmonjard          #+#    #+#              #
#    Updated: 2026/06/19 09:03:39 by sstark           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc

CFLAGS = -Wall -Wextra -Werror -I./$(HEADER_DIR)

HEADER_DIR = includes
HEADERS = minirt.h \
	libft.h \
	parsing.h \
	scene.h \
	util/arrays.h \
	util/colors.h \
	util/cylinders \
	util/planes.h \
	util/spheres.h \
	util/strings.h \

SOURCE_DIR = src
SOURCES = main.c \
	matrices/matrix_cofactor.c \
	matrices/matrix_compare.c \
	matrices/matrix_determinant.c \
	matrices/matrix_identity.c \
	matrices/matrix_inverse.c \
	matrices/matrix_minor.c \
	matrices/matrix_multiply_tuple.c \
	matrices/matrix_multiply.c \
	matrices/matrix_submatrix.c \
	matrices/matrix_transpose.c \
	tuples/tuple_compare.c \
	tuples/tuple_utils.c \
	tuples/tuple_operations.c \
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

TEST_DIR = tests
TESTS = main.c \
		test_tuples.c \
		test_matrices.c

TEST_FILES = $(TESTS:%=$(TEST_DIR)/%)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx
MLX_REPO = https://github.com/42paris/minilibx-linux.git
MLX_INCLUDE = -I$(MLX_DIR)
MLX_LINKS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

LIBUNIT = libunit/framework/libunit.a

HEADER_FILES = $(HEADERS:%=$(HEADER_DIR)/%)
SOURCE_FILES = $(SOURCES:%=$(SOURCE_DIR)/%)

BUILD_DIR = ./build
OBJECT_FILES = $(SOURCES:%.c=$(BUILD_DIR)/src/%.o)
TEST_OBJS = $(TESTS:%.c=$(BUILD_DIR)/tests/%.o)

all: $(LIBFT) $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)
	@echo "[MAKE] $(MLX_DIR)/libmlx.a"
	@$(MAKE) -C $(MLX_DIR) > /dev/null

$(LIBFT):
	@echo "[MAKE]: $(LIBFT_DIR)"
	@make -C $(LIBFT_DIR) bonus

$(LIBUNIT):
	@echo "[GIT] pulling libunit submodule update"
	@git submodule update --init --recursive
	@echo "[MAKE] libunit/framework"
	@$(MAKE) -C libunit/framework > /dev/null

$(NAME): $(OBJECT_FILES)
	@$(CC) $(CFLAGS) $(OBJECT_FILES) $(LIBFT) $(MLX_LINKS) -o $(NAME)

$(BUILD_DIR)/src/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "[COMPILE]: $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR) $(MLX_INCLUDE)

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c | $(LIBUNIT)
	@mkdir -p $(dir $@)
	@echo "[COMPILE TEST]: $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR) -I libunit/framework/inc

test: $(LIBFT) $(LIBUNIT) $(TEST_OBJS) $(OBJECT_FILES)
	@echo "[LINK] test_bin"
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(filter-out $(BUILD_DIR)/src/main.o, $(OBJECT_FILES)) $(LIBFT) -I libunit/framework/inc -L libunit/framework -lunit -lm -o test_bin
	@echo "--- RUNNING TESTS ---"
	@./test_bin

clean:
	@echo "[FCLEAN] $(LIBFT_DIR) $<"
	@make -C $(LIBFT_DIR) fclean
	@echo "[CLEAN] $(MLX_DIR) $<"
	@make -C $(MLX_DIR) clean
	@echo "[CLEAN] libunit"
	@if [ -d libunit/framework ]; then $(MAKE) -C libunit/framework clean; fi
	@rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME) test_bin
	@if [ -d libunit/framework ]; then $(MAKE) -C libunit/framework fclean; fi

re: fclean all

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./$(NAME)
