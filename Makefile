# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/18 20:24:21 by vgauther          #+#    #+#              #
#    Updated: 2019/11/03 20:20:03 by vgauther         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

NAME = xpm_opener

END=$'\x1b[0m
BOLD=$'\x1b[1m'
UNDER=$'\x1b[4m'
REV=$'\x1b[7m'

# Colors
GREY=$'\x1b[30m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m

CC = gcc
CC_FLAGS = -g3 -Wall -Wextra -Werror

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LFT_PATH = ./libft/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

OBJ_NAME = $(SRC_NAME:.c=.o)

INC_NAME = xpm_opener.h

SRC_NAME = 	main.c \
			color.c

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@echo "$(YELLOW)[...] $(NAME) compilation$(END)"
	@$(CC) -o $(NAME) $(OBJ) -lm -L $(LFT_PATH) -lft
	@echo "$(GREEN)[✓] $(NAME) Done$(END)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<

clean:
	@make -C $(LFT_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)[-] $(NAME) .o cleaned$(END)"

fclean:
	@make clean
	@make -C $(LFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)[-] $(NAME) executable cleaned$(END)"


clean_o:
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)

re:
	@make fclean
	@make all
