NAME=ft_db
SRC=main.c \
	parse_argv.c \
	db_exec.c \
	db_prompt.c \
	populate.c \
	set_entry.c \
	create.c \
	parse_entry.c \
	cleanup.c \
	read.c \
	display.c \
	db_delete.c \
	db_update.c
OBJ=$(SRC:.c=.o)
CC=gcc
CFLAGS=-g -Ilibft -Wall -Wextra
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -Llibft -lft -o $(NAME)

$(OBJ): ft_db.h

libft:
	make -C libft

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all
