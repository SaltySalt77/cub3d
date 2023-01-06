# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 15:40:24 by hyna              #+#    #+#              #
#    Updated: 2023/01/06 11:18:43 by nhwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CCFLAGS = -Wall -Werror -Wextra
CCFWRK = -framework OpenGL -framework AppKit
INC_LINK = -I./incs
LIBS = -L./libs/libft -lft\
		-L./libs/mlx -lmlx\

SRCS_DIRS = map_parsing	\
			key_hook	\
			ray_casting	\

SRCS_NAME = main.c \
			mlx_game.c	\
			map_parsing/read_map.c	\
			map_parsing/ft_split2.c	\
			map_parsing/cut_map.c	\
			map_parsing/validate_map.c	\
			map_parsing/padding_map.c	\
			map_parsing/check_vec.c	\
			map_parsing/save_texture.c	\
			map_parsing/validate_map2.c	\
			map_parsing/set_dir_plane.c	\
			key_hook/key_dir.c	\
			key_hook/key_rotate.c	\
			key_hook/key_p_r.c	\
			ray_casting/ray_cast.c	\
			ray_casting/paint.c	\

SRCS_PATH = ./srcs
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))

OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS_PATH = ./objs
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))
DIRS = $(addprefix $(OBJS_PATH)/, $(SRCS_DIRS))

all : $(NAME)

$(NAME) : $(DIRS) $(OBJS)
	@$(MAKE) -C ./libs/libft all
	@$(MAKE) -C ./libs/mlx all
	@cp ./libs/mlx/libmlx.dylib ./
	$(CC) $(CCFWRK) $(CCFLAGS) $(LIBS) -o $(NAME) $(OBJS)

$(DIRS) :
	mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(DIRS) 2> /dev/null || true

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c
	$(CC) $(INC_LINK) $(CCFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C ./libs/libft clean
	@$(MAKE) -C ./libs/mlx clean
	rm -rf $(OBJS_PATH)

fclean : clean
	rm -rf ./libs/libft/libft.a
	rm -rf ./libs/mlx/libmlx.dylib
	rm -rf ./libmlx.dylib
	rm -rf $(NAME)
re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean bonus