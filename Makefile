NAME = ft_db
SRC = main.c \
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
	db_update.c \
	get_uids.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -g -Ilibft -Wall -Wextra


$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

all: $(NAME)

clean:
	make -C ./libft clean
	rm -f $(OBJ)

fclean:
	make -C ./libft fclean
	rm -f $(OBJ) $(NAME)

re: fclean $(NAME)
