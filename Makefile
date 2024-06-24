# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylamouri <ylamouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 14:32:29 by ylamouri          #+#    #+#              #
#    Updated: 2024/06/24 17:12:16 by ylamouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

LIBFT_DIR = Libft

LIBFT = $(LIBFT_DIR)/libft.a

SERVER = server
CLIENT = client

SV_SRCS = srcs/server.c
SV_OBJS = $(SV_SRCS:.c=.o)

CLIENT_SRCS = srcs/client.c srcs/utils.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

all: $(SERVER) $(CLIENT) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
$(SERVER): $(SV_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SV_OBJS) $(LIBFT)  -o server
$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT)  -o client 
	
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(SV_OBJS) $(CLIENT_OBJS) 

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(SERVER) $(CLIENT)

re: fclean all
