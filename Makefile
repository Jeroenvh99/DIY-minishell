# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/28 12:06:53 by dbasting      #+#    #+#                  #
#    Updated: 2023/05/08 18:14:41 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		:= minishell

SRC_FILES	:= main.c\
			cmd.c\
			expand.c\
			expand_fieldsplit.c\
			expand_spec_exit.c\
			expand_spec_nparam.c\
			expand_spec_opts.c\
			expand_spec_pid.c\
			expand_spec_pos.c\
			expand_spec_shname.c\
			expand_utils.c\
			expand_var.c\
			lex.c\
			lex_token_get.c\
			lex_utils.c\
			parse.c\
			parse_in.c\
			parse_operator.c\
			parse_out.c\
			parse_pipe.c\
			parse_utils.c\
			parse_word.c\
			readcmdline.c\
			token.c\
			utils_list.c\
			utils_quotes.c\
			var.c\
			\
			debug.c
OBJ_FILES	:= $(patsubst %.c,%.o,$(SRC_FILES))
HDR_FILES	:= msh.h\
			msh_error.h\
			msh_expand.h\
			msh_parse.h\
			msh_var.h\
			\
			msh_debug.h
LIB_FILES	:= libft.a

SRC_DIR		:= ./source/
SRC_SUBDIRS	:= builtins/ test/
OBJ_DIR		:= ./object/
OBJ_SUBDIRS := $(SRC_SUBDIRS)
HDR_DIR		:= ./header/
LIB_DIR		:= ./lib/

CFLAGS		:= -Wall -Wextra -Werror -I$(LIB_DIR)libft/include/ -I$(HDR_DIR) -g -fsanitize=address

.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(NAME)
	@echo "Bonus is basis, vrind."

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES)) $(addprefix $(LIB_DIR),$(LIB_FILES))
	@$(CC) $(CFLAGS) $^ -lreadline -o $@

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

re: fclean all
