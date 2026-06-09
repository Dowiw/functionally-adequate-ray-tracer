# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 16:36:57 by kmonjard          #+#    #+#              #
#    Updated: 2025/09/11 16:36:58 by kmonjard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
C_FLAGS = -Wall -Werror -Wextra -g

SRC_DIR = ./src
LIBFT = $(SRC_DIR)/libft/libft.a

MLX_DIR = ./mlx
MLX_REPO = https://github.com/42paris/minilibx-linux.git
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

C_FILES = ...

SRC = $(addprefix $(SRC_DIR)/, $(C_FILES))

OBJ = $(SRC:.c=.o)

INCLUDES = ./includes

#  -- Rules  --
all: $(LIBFT) $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR) > /dev/null

$(LIBFT):
	make -C $(SRC_DIR)/libft/

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(C_FLAGS) -c $< -o $@ -I$(INCLUDES) -I$(MLX_DIR)

bonus: $(LIBFT) $(O_BONUS)
	@$(CC) $(C_FLAGS) $(O_BONUS) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

clean:
	@make -C ./src/libft clean
	@echo "Deleting object files in fdf..."
	@rm -f $(OBJ) $(O_BONUS)

fclean:
	@make -C ./src/libft fclean
	@echo "Deleting object files in fdf..."
	@echo "Deleting all binaries in fdf..."
	@rm -f $(NAME)
	@rm -f $(OBJ) $(O_BONUS)

re: fclean all

.PHONY: all clean fclean re
