# Project settings
NAME = minishell
CC = cc
ARCH := $(shell uname -m)
ifneq ($(ARCH),x86_64)
	CFLAGS = -arch $(ARCH) -Wall -Wextra -lreadline
else
	CFLAGS = -Wall -Wextra -lreadline
endif

SRCS =	src/main.c					\
		src/utils.c					\
		src/parsing/p_parse.c		\
		src/parsing/p_tokenizer.c	\
		src/parsing/p_utils.c		\
		src/parsing/p_booleans.c	\
		

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: libft_check $(LIBFT) $(NAME)

libft_check:
ifneq ($(wildcard $(LIBFT_DIR)),)
	@echo "Libft found!"
else
	@echo "Libft not found, downloading library from https://github.com/Db1zz/libft"
	git clone https://github.com/Db1zz/libft libft
	rm -rf ./libft/.git
endif

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re