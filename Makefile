NAME := pipex
INCLUDE = include
LIBFT = libft
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
SRCS := pipex.c\
        pipex_utils.c\

all: $(NAME)

$(NAME) :
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -Ilibft/ -Llibft/ -lft -o pipex

clean:
	@make clean -C $(LIBFT)

fclean: clean
	rm -rf pipex
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
