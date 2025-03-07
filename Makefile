NAME_C = client
NAME_S = server
CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRC_C = client.c
SRC_S = server.c
SRC_P = ft_printf/libftprintf.a

OBJC = $(SRC_C:.c=.o)
OBJS = $(SRC_S:.c=.o)

all:$(NAME_S) $(NAME_C)

$(NAME_S): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME_S) $(OBJS) $(SRC_P)

$(NAME_C): $(OBJC)
	$(CC) $(CFLAGS) -o $(NAME_C) $(OBJC) $(SRC_P)

clean:
	rm -rf $(OBJC) $(OBJS)
fclean: clean
	rm -rf $(NAME_S) $(NAME_C)

re: fclean all
