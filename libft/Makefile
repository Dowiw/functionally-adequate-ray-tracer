# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/12 11:40:15 by kmonjard          #+#    #+#              #
#    Updated: 2025/05/12 11:40:17 by kmonjard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I../includes -I../includes/libft

#Alt + Z to wrap a line for readability in VSC
C_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	 ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
	 ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
	 ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
	 ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c \
	 ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	 get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	 printf/ft_printf.c printf/ft_putchar.c printf/ft_puthex_low.c \
	 printf/ft_putint_u.c printf/ft_putptr.c printf/ft_putstr.c \
	 printf/ft_putint.c printf/ft_puthex_up.c ft_strtol.c ft_isspace.c \
	 ft_strncpy.c ft_strcmp.c ft_swap.c

BONUS_FILES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c \
	 ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c \
	 ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

O_BONUS = $(BONUS_FILES:.c=.o)

O_FILES = $(C_FILES:.c=.o)

all: bonus

$(NAME): $(O_FILES)
	@ar rcs $(NAME) $(O_FILES)

bonus: $(O_FILES) $(O_BONUS)
	@echo "[ARCHIVE] Creating libft.a"
	@ar rcs $(NAME) $(O_FILES) $(O_BONUS)

%.o: %.c
	@echo "[COMPILE] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "[DELETE] Removing object files in libft"
	@rm -f $(O_FILES) $(O_BONUS)

fclean: clean
	@echo "[DELETE] Removing all binaries in libft"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
