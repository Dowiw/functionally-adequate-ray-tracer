NAME = miniRT

CUR_DIR = $(shell pwd)

HEADER_DIR = include

HEADERS = minirt.h

SOURCE_DIR = src

SOURCES = main.c

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

HEADER_FILES = $(HEADERS:%=$(HEADER_DIR)/%)

SOURCE_FILES = $(SOURCES:%=$(SOURCE_DIR)/%)

BUILD_DIR = build

OBJECT_FILES = $(SOURCES:%.c=$(BUILD_DIR)/%.o)

DEP_FILES = $(OBJECT_FILES:.o=.d)

CC = cc

CFLAGS += -Wall -Wextra -Werror -I$(CUR_DIR)/$(HEADER_DIR) -MMD -MP

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	make -C $(LIBFT_DIR) bonus
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(LIBFT) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) fclean
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

only: all clean

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./$(NAME)

-include $(DEP_FILES)
