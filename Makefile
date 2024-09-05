# Project settings
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	main.c	\

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re