# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/09 20:02:32 by kmonjard          #+#    #+#              #
#    Updated: 2026/08/14 20:01:34 by sstark           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I./$(HEADER_DIR)

HEADER_DIR = includes
HEADERS = minirt.h \
	debug.h \
	input.h \
	libft/libft.h \
	parsing.h \
	ray.h \
	rendering.h \
	scene.h \
	util/arrays.h \
	util/colors.h \
	util/cones.h \
	util/cylinders.h \
	util/planes.h \
	util/spheres.h \
	util/strings.h \

SOURCE_DIR = src
SOURCES = main.c \
	debug/debug.c \
	graphics/canvas.c \
	graphics/mlx.c \
	input/controls.c \
	input/input.c \
	matrices/matrix_cofactor.c \
	matrices/matrix_compare.c \
	matrices/matrix_determinant.c \
	matrices/matrix_identity.c \
	matrices/matrix_inverse.c \
	matrices/matrix_minor.c \
	matrices/matrix_multiply_tuple.c \
	matrices/matrix_multiply.c \
	matrices/matrix_rotation.c \
	matrices/matrix_scaling.c \
	matrices/matrix_shearing.c \
	matrices/matrix_submatrix.c \
	matrices/matrix_translation.c \
	matrices/matrix_transpose.c \
	matrices/view_transform.c \
	tuples/tuple_compare.c \
	tuples/tuple_utils.c \
	tuples/tuple_operations.c \
	tuples/tuple_constructs.c \
	parsing/parse_ambience.c \
	parsing/parse_camera.c \
	parsing/parse_color.c \
	parsing/parse_cylinder.c \
	parsing/parse_double.c \
	parsing/parse_error.c \
	parsing/parse_int.c \
	parsing/parse_light.c \
	parsing/parse_plane.c \
	parsing/parse_point.c \
	parsing/parse_sphere.c \
	parsing/parse_tuple.c \
	parsing/parse_vector.c \
	parsing/parsing.c \
	rays/intersections.c \
	rays/intersect.c \
	rays/ray_transform.c \
	rays/ray.c \
	rendering/computations.c \
	rendering/drawing.c \
	rendering/rendering.c \
	scene/camera.c \
	scene/scene.c \
	util/arrays/arrays1.c \
	util/arrays/arrays2.c \
	util/arrays/cones/cones.c \
	util/arrays/cones/cone_utils.c \
	util/arrays/cylinders/cylinders.c \
	util/arrays/cylinders/cylinder_utils.c \
	util/arrays/intersections/intersections1.c \
	util/arrays/intersections/intersections2.c \
	util/arrays/objects/normal.c \
	util/arrays/planes/planes.c \
	util/arrays/spheres/sphere.c \
	util/colors/colors_grayscale.c \
	util/colors/colors_util.c \
	util/colors/colors1.c \
	util/lighting/lighting.c \
	util/materials/materials.c \
	util/strings/strings1.c \
	util/shadows/shadows.c

TEST_DIR = tests
TESTS = main.c \
	test_tuples.c \
	test_colors.c \
	test_canvas.c \
	test_matrices.c \
	test_transformations.c \
	test_rays.c \
	test_light_shading.c \
	test_rendering.c \
	test_shadows.c \
	test_planes.c \
	test_cylinders.c \
	test_cones.c

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

all: $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)
	@echo "[MAKE] $(MLX_DIR)/libmlx.a"
	@$(MAKE) -C $(MLX_DIR) > /dev/null

$(LIBFT):
	@echo "[MAKE]: $(LIBFT_DIR)"
	@make -C $(LIBFT_DIR) bonus

$(LIBUNIT):
	@echo "[MAKE] libunit/framework"
	@$(MAKE) -C libunit/framework > /dev/null

$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(OBJECT_FILES)
	@$(CC) $(CFLAGS) $(OBJECT_FILES) $(LIBFT) $(MLX_LINKS) -o $(NAME)

$(BUILD_DIR)/src/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(dir $@)
	@echo "[COMPILE]: $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR) $(MLX_INCLUDE)

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c $(HEADER_FILES) | $(LIBUNIT)
	@mkdir -p $(dir $@)
	@echo "[COMPILE TEST]: $<"
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_DIR) -Ilibunit/framework/inc

test: $(LIBFT) $(LIBUNIT) $(TEST_OBJS) $(OBJECT_FILES) $(MLX_DIR)/libmlx.a
	@echo "[LINK] test_bin"
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(filter-out $(BUILD_DIR)/src/main.o, $(OBJECT_FILES)) $(LIBFT) $(MLX_LINKS) -Ilibunit/framework/inc -Llibunit/framework -lunit -lm -o test_bin
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

bear:
	@make clean
	bear -- $(MAKE) all
	bear --append -- $(MAKE) test
	@mkdir -p .configs
	mv compile_commands.json .configs/

.PHONY: all clean fclean re test valgrind bear

