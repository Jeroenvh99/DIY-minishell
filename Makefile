# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/28 12:06:53 by dbasting      #+#    #+#                  #
#    Updated: 2023/06/20 21:51:13 by dbasting      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		:= minishell

OS			:= $(shell uname -s)

SRC_FILES	:= main.c\
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
			lex/token.c\
			lex/lex_token_get.c\
			lex/lex_utils.c\
			minishell/cmd.c\
			minishell/error.c\
			minishell/heredoc.c\
			minishell/readcmdline.c\
			minishell/msh_loop.c\
			minishell/signal.c\
			parse/parse.c\
			parse/parse_cmd.c\
			parse/parse_in.c\
			parse/parse_operator.c\
			parse/parse_out.c\
			parse/parse_pipe.c\
			parse/parse_utils.c\
			parse/parse_word.c\
			utils/utils_list.c\
			utils/utils_quotes.c\
			var/var.c\
			var/var_parse.c\
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
SRC_SUBDIRS	:= builtins/ env/ execute/ expand/ lex/ minishell/ parse/ test/ utils/ var/
OBJ_DIR		:= ./object/
OBJ_SUBDIRS := $(SRC_SUBDIRS)
HDR_DIR		:= ./include/
LIB_DIR		:= ./lib/

CFLAGS		:= -Wall -Wextra -Werror -I$(LIB_DIR)libft/include/ -I$(HDR_DIR) -g -fsanitize=address
LDFLAGS	:= -lreadline
ifeq ($(OS),Darwin)
LDFLAGS	+= -L$(HOME)/.brew/opt/readline/lib/ 
CFLAGS	+= -I$(HOME)/.brew/opt/readline/include
endif

.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: $(NAME)
	@echo "Bonus is basis, vrind."

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES)) $(addprefix $(LIB_DIR),$(LIB_FILES))
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

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

test_cd:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/cd.c source/builtins/env_utils.c source/env/env_search.c source/env/env_set.c source/env/env_utils.c source/var_parse.c source/builtins/cd_test/cd_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_echo:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/echo.c source/builtins/echo_test/echo_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_env:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/env.c source/builtins/env_utils.c source/builtins/env_test/env_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_exit:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/exit.c source/builtins/exit_test/exit_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_export:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/export.c source/builtins/export_test/export_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_pwd:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/pwd.c source/builtins/pwd_test/pwd_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_unset:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/unset.c source/builtins/env_utils.c source/builtins/unset_test/unset_unittest.c lib/libft/libft.a && ./a.out
	rm a.out
