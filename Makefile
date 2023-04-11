# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/28 12:06:53 by dbasting      #+#    #+#                  #
#    Updated: 2023/04/07 16:36:03 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 			:= philo
NAME_BONUS		:= philo_bonus

SRC_FILES		:= env.c\
				timestamp.c\
				utils.c
SRC_FILES_MNDTR	:= $(SRC_FILES)\
				main.c\
				philo.c\
				philo_eat.c\
				philo_sleep.c\
				philo_think.c
SRC_FILES_BONUS	:= $(SRC_FILES)
OBJ_FILES		:= $(SRC_FILES:.c=.o)
OBJ_FILES_MNDTR := $(SRC_FILES_MNDTR:.c=.o)
OBJ_FILES_BONUS	:= $(SRC_FILES_BONUS:.c=.o)
HDR_FILES		:= philo.h\
				philo_utils.h

SRC_DIR			:= ./source/
OBJ_DIR			:= ./object/
HDR_DIR			:= ./header/

CFLAGS			:= -Wall -Wextra -Werror -I$(HDR_DIR)

.PHONY: $(NAME) all bonus clean fclean re

all: $(NAME) $(NAME_BONUS)

bonus: $(NAME_BONUS)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES_MNDTR))
	@$(CC) $(CFLAGS) $^ -lpthread -o $@

$(NAME_BONUS): $(addprefix $(OBJ_DIR),$(OBJ_FILES_BONUS))
	@echo "..."
	@#$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HDR_DIR),$(HDR_FILES))
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(HDR_DIR) $< -c -o $@

clean:
	@rm -f $(OBJ_DIR)*.o

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all
