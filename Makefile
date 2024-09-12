# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 17:22:05 by tabadawi          #+#    #+#              #
#    Updated: 2024/09/12 17:26:47 by tabadawi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
CFLAGS	+=	-fsanitize=address -g3
SRCS 	=	cub3d.c
OBJS	=	$(SRCS:.c=.o)
LIBFT	=	libft/libft.a
MLX		=	mlx/libmlx.a
MLXFLAG	=	-L mlx -lmlx -framework OpenGL -framework AppKit

all		:	$(NAME)

$(LIBFT):
	@$(MAKE)	-C libft

$(MLX):
	@$(MAKE)  -C mlx

$(NAME)	: $(OBJS) $(LIBFT)  $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAG) -o $@ $(LIBFT) $(MLX)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C libft clean
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C libft fclean
	@$(MAKE) -C mlx clean
	@rm -f $(NAME)

re:	fclean all
 
.PHONY: all clean fclean re