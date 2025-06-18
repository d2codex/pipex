# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 08:40:31 by diade-so          #+#    #+#              #
#    Updated: 2025/06/18 13:46:16 by diade-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               Compiler & Flags                               #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra -g3
INCLUDES = -I./libft/includes -I./includes

# **************************************************************************** #
#                                 Target Name                                  #
# **************************************************************************** #

NAME = pipex

# **************************************************************************** #
#                                 Directories                                  #
# **************************************************************************** #

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
BONUS_DIR = bonus

# **************************************************************************** #
#                                Source Files                                  #
# **************************************************************************** #

SRC = $(addprefix $(SRC_DIR)/, main.c utils.c path_utils.c smart_split.c \
	exec.c validate.c)

SHARED = utils.c path_utils.c smart_split.c

BONUS_SRC = $(addprefix $(BONUS_DIR)/, main_bonus.c utils_bonus.c exec_bonus.c \
	validate_bonus.c)

# **************************************************************************** #
#                                Object Files                                  #
# **************************************************************************** #

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

SHARED_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SHARED:.c=.o)))

BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_SRC:.c=.o)))

ALL_BONUS_OBJ = $(BONUS_OBJ) $(SHARED_OBJ)

# **************************************************************************** #
#                                    Libft                                     #
# **************************************************************************** #

LIBFT = $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                   Rules                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

bonus: $(ALL_BONUS_OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(INCLUDES) $(ALL_BONUS_OBJ) $(LIBFT) -o pipex_bonus

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME) pipex_bonus

re: fclean all

.PHONY: all clean fclean re bonus
