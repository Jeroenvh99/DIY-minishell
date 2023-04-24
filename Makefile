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
			lex_tokenize.c\
			lex_utils.c
OBJ_FILES	:= $(patsubst %.c,%.o,$(SRC_FILES))
HDR_FILES	:= msh.h\
			msh_error.h\
			msh_lex.h\
			msh_parse.h
LIB_FILES	:= libft.a

SRC_DIR		:= ./source/
SRC_SUBDIRS	:= builtins/ test/
OBJ_DIR		:= ./object/
OBJ_SUBDIRS := $(SRC_SUBDIRS)
HDR_DIR		:= ./header/
LIB_DIR		:= ./lib/

CFLAGS		:= -Wall -Wextra -Werror -I$(LIB_DIR)libft/include/ -I$(HDR_DIR)

.PHONY: all bonus clean fclean re

all: $(NAME)


bonus: $(NAME)
	@echo "Bonus is basis, vrind."

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES)) $(addprefix $(LIB_DIR),$(LIB_FILES))
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HDR_DIR),$(HDR_FILES))
	@mkdir -p $(addprefix $(OBJ_DIR),$(OBJ_SUBDIRS))
	@$(CC) $(CFLAGS) -I$(HDR_DIR) $< -c -o $@

$(LIB_DIR)%.a:
	@$(MAKE) -j --directory=$(LIB_DIR)

clean:
	@$(MAKE) -j --directory=$(LIB_DIR) clean
	@rm -f $(addprefix $(OBJ_DIR),$(OBJ_FILES))

fclean: clean
	@$(MAKE) -j --directory=$(LIB_DIR) fclean
	@rm -f $(NAME)


