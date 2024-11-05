CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =	get_next_line.c \
		get_next_line_utils.c
HEADER = get_next_line.h

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OBJS)

re: fclean all

.PHONY: all clean fclean re