NAME_C = client
NAME_S = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRC_C = client.c
SRC_S = server.c
SRC_P = ft_printf/libftprintf.a
SRC_CB = client_bonus.c
SRC_SB = server_bonus.c

OBJC = $(SRC_C:.c=.o)
OBJS = $(SRC_S:.c=.o)
OBJCB = $(SRC_CB:.c=.o)
OBJSB = $(SRC_SB:.c=.o)

all:$(NAME_S) $(NAME_C)
bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_S): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME_S) $(OBJS) $(SRC_P)

$(NAME_C): $(OBJC)
	$(CC) $(CFLAGS) -o $(NAME_C) $(OBJC) $(SRC_P)

$(NAME_CLIENT_BONUS): $(OBJCB)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) $(OBJCB) $(SRC_P)

$(NAME_SERVER_BONUS): $(OBJSB)
	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) $(OBJSB) $(SRC_P)

clean:
	rm -rf $(OBJC) $(OBJS) $(OBJCB) $(OBJSB)
fclean: clean
	rm -rf $(NAME_S) $(NAME_C) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all
