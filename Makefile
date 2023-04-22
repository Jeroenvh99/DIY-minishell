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

NAME 		:= minishell

SRC_FILES	:= test/main.c\
			lex.c\
			lex_tokenize.c
OBJ_FILES	:= $(patsubst %.c,%.o,$(notdir $(SRC_FILES)))
HDR_FILES	:= msh.h\
			lex.h\
			parse.h
LIB_FILES	:= libft.a

SRC_DIR		:= ./source/
OBJ_DIR		:= ./object/
HDR_DIR		:= ./header/
LIB_DIR		:= ./lib/

VPATH		:= $(SRC_DIR) $(SRC_DIR)builtins $(SRC_DIR)test

CFLAGS		:= -Wall -Wextra -Werror -I$(LIB_DIR)libft/include/ -I$(HDR_DIR)

.PHONY: all bonus clean fclean re

all: $(NAME)


bonus: $(NAME)
	@echo "Bonus is basis, vrind."

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES)) $(addprefix $(LIB_DIR),$(LIB_FILES))
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: %.c $(addprefix $(HDR_DIR),$(HDR_FILES))
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(HDR_DIR) $< -c -o $(OBJ_DIR)$*.o

$(LIB_DIR)%.a:
	$(MAKE) -j --directory=$(LIB_DIR)

clean:
	@rm -f $(OBJ_DIR)*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
