# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyna <hyna@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 15:40:24 by hyna              #+#    #+#              #
#    Updated: 2022/12/26 13:25:06 by hyna             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CCFLAGS = -Wall -Werror -Wextra
INC_LINK = -I./incs
LIBS = -L./libs/libft -lft\

SRCS_DIRS = tmp # 현재의 Makefile 돌아가려면 이 메크로 필수로 필요함

SRCS_NAME = main.c \

SRCS_PATH = ./srcs
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))

OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS_PATH = ./objs
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))
DIRS = $(addprefix $(OBJS_PATH)/, $(SRCS_DIRS))

all : $(NAME)

$(NAME) : $(DIRS) $(OBJS)
	@$(MAKE) -C ./libs/libft all
	$(CC) $(CCFLAGS) -o $(NAME) $(OBJS)

$(DIRS) :
	mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(DIRS) 2> /dev/null || true

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c
	$(CC) $(INC_LINK) $(CCFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C ./libs/libft clean
	rm -rf $(OBJS_PATH)

fclean : clean
	rm -rf ./libs/libft/libft.a
	rm -rf $(NAME)
re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean bonus