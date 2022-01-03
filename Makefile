NAME_H = minitalk.h

SERVER_SRCS = server.c minitalk_utils.c
CLIENT_SRCS = client.c minitalk_utils.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEL = rm -rf

all: server client

client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o client

server: $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o server

%.o:%.c $(NAME_H)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(DEL) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean:clean
	$(DEL) client server

re : clean client server