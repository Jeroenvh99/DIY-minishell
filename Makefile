# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/28 12:06:53 by dbasting      #+#    #+#                  #
#    Updated: 2023/05/15 15:38:26 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		:= minishell

SRC_FILES	:= main.c\
			cmd.c\
			env/env.c\
			env/env_search.c\
			env/env_set.c\
			env/env_unset.c\
			env/env_utils.c\
			expand/expand.c\
			expand/expand_fieldsplit.c\
			expand/expand_spec_exit.c\
			expand/expand_spec_nparam.c\
			expand/expand_spec_opts.c\
			expand/expand_spec_pid.c\
			expand/expand_spec_pos.c\
			expand/expand_spec_shname.c\
			expand/expand_utils.c\
			expand/expand_var.c\
			lex/lex.c\
			lex/lex_token_get.c\
			lex/lex_utils.c\
			parse/parse.c\
			parse/parse_in.c\
			parse/parse_operator.c\
			parse/parse_out.c\
			parse/parse_pipe.c\
			parse/parse_utils.c\
			parse/parse_word.c\
			readcmdline.c\
			token.c\
			utils_list.c\
			utils_quotes.c\
			var.c\
			var_parse.c\
			\
			debug.c
OBJ_FILES	:= $(patsubst %.c,%.o,$(SRC_FILES))
HDR_FILES	:= msh.h\
			msh_error.h\
			msh_env.h\
			msh_expand.h\
			msh_parse.h\
			msh_var.h\
			\
			msh_debug.h
LIB_FILES	:= libft.a

SRC_DIR		:= ./source/
SRC_SUBDIRS	:= builtins/ env/ expand/ lex/ parse/ test/
OBJ_DIR		:= ./object/
OBJ_SUBDIRS := $(SRC_SUBDIRS)
HDR_DIR		:= ./include/
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
