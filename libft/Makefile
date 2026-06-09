NAME = libft.a

CUR_DIR = $(shell pwd)

HEADERS = libft.h \
	  ft_printf.h \
	  get_next_line.h

SOURCES = ft_atoi.c \
	  ft_bzero.c \
	  ft_calloc.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_itoa.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_putchar_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_putstr_fd.c \
	  ft_split.c \
	  ft_strchr.c \
	  ft_strdup.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_strmapi.c \
	  ft_strncmp.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strtrim.c \
	  ft_substr.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_printchar.c \
	  ft_printf.c \
	  ft_printnbr.c \
	  ft_printptr.c \
	  ft_printstr.c \
	  ft_printunbr_base.c \
	  ft_printunbr_hex.c \
	  ft_printunbr_hexup.c \
	  ft_printunbr.c \
	  get_next_line_utils.c \
	  get_next_line.c

BONUS = ft_lstadd_back.c \
	  ft_lstadd_front.c \
	  ft_lstclear.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstlast.c \
	  ft_lstmap.c \
	  ft_lstnew.c \
	  ft_lstsize.c

HEADER_FILES = $(HEADERS)

SOURCE_FILES = $(SOURCES)

BONUS_SOURCE_FILES = $(BONUS)

OBJECT_FILES = $(SOURCE_FILES:.c=.o)

BONUS_OBJECT_FILES = $(BONUS_SOURCE_FILES:.c=.o)

TEST_FILES = $(SOURCE_FILES:.c=.out)

CFLAGS += -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECT_FILES) $(HEADER_FILES)
	ar rcs $(NAME) $(OBJECT_FILES)

bonus: $(OBJECT_FILES) $(HEADER_FILES) $(BONUS_OBJECT_FILES)
	ar rcs $(NAME) $(OBJECT_FILES) $(BONUS_OBJECT_FILES)

clean:
	rm -f $(OBJECT_FILES) $(BONUS_OBJECT_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

check:
	@issues=0; \
	for file in $(filter-out $(SOURCE_FILES) $(BONUS_SOURCE_FILES), $(wildcard *.c)); do \
		echo $$file is missing from SOURCES!; \
		issues=$$((issues+1)); \
	done; \
	for file in $(filter-out $(wildcard *.c), $(SOURCE_FILES) $(BONUS_SOURCE_FILES)); do \
		echo $$file does not exist!; \
		issues=$$((issues+1)); \
	done; \
	for norm in "$(shell norminette | grep -v OK!$)"; do \
		echo $$norm; \
		issues=$$((issues+1)); \
	done; \
	echo Check completed with $$issues issues.

test: $(TEST_FILES)

$(TEST_FILES): $(OBJECT_FILES) $(BONUS_OBJECT_FILES)
	@sed 's\^[/][*]$$\\g' $(@:.out=.c) | sed 's\^[*][/]$$\\g' > $(@:.out=-copy.c);
	@cc $(CFLAGS) $(@:.out=-copy.c) $(filter-out $(@:.out=.o), $(OBJECT_FILES) $(BONUS_OBJECT_FILES)) -lbsd -o $(@); \
	rm $(@:.out=-copy.c); \
	echo -n .

tclean: fclean
	rm -f $(SOURCE_FILES:.c=-copy.c)
	rm -f $(SOURCE_FILES:.c=.out)
