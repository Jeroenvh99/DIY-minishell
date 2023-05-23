# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/28 12:06:53 by dbasting      #+#    #+#                  #
#    Updated: 2023/05/22 16:24:36 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		:= msh_test_env

MAIN_SRC	:= test_env.c
SRC_FILES	:= \
			error.c\
			env/env.c\
			env/env_search.c\
			env/env_set.c\
			env/env_unset.c\
			env/env_utils.c\
			var.c\
			var_parse.c
MAIN_OBJ	:= $(patsubst %.c,%.o,$(MAIN_SRC))
OBJ_FILES	:= $(patsubst %.c,%.o,$(SRC_FILES))
HDR_FILES	:= msh.h\
			msh_error.h\
			msh_env.h\
			msh_var.h
LIB_FILES	:= libft.a

SRC_DIR		:= ../../source/
SRC_SUBDIRS	:= env/
OBJ_DIR		:= ./object/
OBJ_SUBDIRS := $(SRC_SUBDIRS)
HDR_DIR		:= ../../include/
LIB_DIR		:= ../../lib/

CFLAGS		:= -Wall -Wextra -Werror -I$(LIB_DIR)libft/include/ -I$(HDR_DIR) -g -fsanitize=address

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES)) $(MAIN_OBJ) $(addprefix $(LIB_DIR),$(LIB_FILES))
	@$(CC) $(CFLAGS) $^ -lreadline -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	@$(CC) $(CFLAGS) -I$(HDR_DIR) $< -c -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HDR_DIR),$(HDR_FILES))
	@mkdir -p $(addprefix $(OBJ_DIR),$(OBJ_SUBDIRS))
	@$(CC) $(CFLAGS) -I$(HDR_DIR) $< -c -o $@

$(LIB_DIR)%.a:
	@$(MAKE) -j --directory=$(LIB_DIR)

clean:
	@$(MAKE) -j --directory=$(LIB_DIR) clean
	@rm -f $(addprefix $(OBJ_DIR),$(OBJ_FILES))
	@rm -f main.o

fclean: clean
	@$(MAKE) -j --directory=$(LIB_DIR) fclean
	@rm -f $(NAME)

re: fclean all
