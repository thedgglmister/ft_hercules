CLIENT = client

SERVER = server

C_SRCS = ft_hydra_client.c

S_SRCS = ft_hydra_server.c ft_reap_zombies.c

SRCS = $(S_SRCS) $(C_SRCS)

C_OBJS = $(C_SRCS:.c=.o)

S_OBJS = $(S_SRCS:.c=.o)

OBJS = $(S_OBJS) $(C_OBJS)

LIB = libft/libft.a

GCC = gcc -Wall -Wextra -Werror -I libft/includes




all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS)
	@gcc $(C_OBJS) $(LIB) -o $(CLIENT)

$(SERVER): $(OBJS)
	@gcc $(S_OBJS) $(LIB) -o $(SERVER)

$(OBJS): $(SRCS) $(LIB)
	@$(GCC) -c $(SRCS)

$(LIB):
	@make -C libft

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(CLIENT) $(SERVER)

re: fclean all
