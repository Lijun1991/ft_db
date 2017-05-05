NAME = ft_db
SRC = main.c \
	  parse_argv.c \
	  db_exec.c \
	  db_prompt.c \
	  db_populate.c \
	  set_entry.c \
	  db_create.c \
	  parse_entry.c \
	  cleanup.c \
	  db_read.c \
	  display.c \
	  db_delete.c \
	  db_update.c \
	  get_uids.c \
	  data.c
OBJ = $(SRC:.c=.o)
	CC = gcc
	CFLAGS = -g -Ilibft -Wall -Wextra -Werror


$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft

all: $(NAME)

$(OBJ): ft_db.h

clean:
	make -C ./libft clean
	rm -f $(OBJ)

fclean:
	make -C ./libft fclean
	rm -f $(OBJ) $(NAME)

re: fclean $(NAME)
