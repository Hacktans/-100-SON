CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g

NAME = minishell

SRC = minishell.c  utils.c ft_tokenize.c parsing.c ft_reader.c builtins.c quote_chk.c esc_seq.c ft_echo.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

RL_LIB = -lreadline

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJ) $(LIBFT) $(RL_LIB) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re