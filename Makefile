# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dbasting <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/28 12:06:53 by dbasting      #+#    #+#                  #
#    Updated: 2023/08/11 10:43:18 by jvan-hal      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		:= minishell

OS			:= $(shell uname -s)

SRC_FILES	:= main.c\
			builtins/cd.c\
			builtins/echo.c\
			builtins/env.c\
			builtins/exit.c\
			builtins/export.c\
			builtins/pwd.c\
			builtins/unset.c\
			env/env.c\
			env/env_append_val.c\
			env/env_basevars.c\
			env/env_search.c\
			env/env_set.c\
			env/env_set_main.c\
			env/env_unset.c\
			env/env_update.c\
			env/env_utils.c\
			execute/execute.c\
			execute/execute_cmd.c\
			execute/execute_fork.c\
			execute/path.c\
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
			parse/parse_pipeline.c\
			parse/parse_utils.c\
			parse/parse_word.c\
			utils/utils_list.c\
			utils/utils_quotes.c\
			var/var.c\
			var/var_parse.c\
			var/var_utils.c\
			\
			debug.c
OBJ_FILES	:= $(patsubst %.c,%.o,$(SRC_FILES))
HDR_FILES	:= msh.h\
			msh_error.h\
			msh_env.h\
			msh_execute.h\
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
	cc $(CFLAGS) -lcriterion source/builtins/cd.c source/env/env.c source/env/env_append_val.c source/env/env_search.c source/env/env_set.c source/env/env_set_main.c source/env/env_update.c source/env/env_utils.c source/env/env_basevars.c source/minishell/error.c source/var/var_parse.c test/builtins/cd/cd_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_echo:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/echo.c test/builtins/echo/echo_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_env:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/env.c source/env/env_append_val.c source/env/env_utils.c test/builtins/env/env_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_export:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/export.c source/env/env.c source/env/env_append_val.c source/env/env_utils.c source/env/env_search.c source/env/env_set.c source/env/env_set_main.c source/env/env_basevars.c source/var/var_parse.c test/builtins/export/export_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_pwd:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/builtins/pwd.c test/builtins/pwd/pwd_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_unset:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/env/env_append_val.c source/builtins/unset.c source/env/env.c source/env/env_unset.c source/env/env_basevars.c source/env/env_utils.c source/env/env_search.c source/env/env_set.c source/env/env_set_main.c source/env/env_basevars.c source/var/var_parse.c source/var/var_utils.c test/builtins/unset/unset_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_lexer:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/lex/token.c test/msh/lex/lex_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_expander:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion test/msh/expand/expand_unittest.c lib/libft/libft.a && ./a.out
	rm a.out

test_parser:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion test/msh/parse/parse_unittest.c source/parse/parse_utils.c lib/libft/libft.a && ./a.out
	rm a.out

test_msh_env:
	$(MAKE) -j -C lib/libft
	cc $(CFLAGS) -lcriterion source/env/env.c source/env/env_utils.c source/env/env_search.c source/env/env_unset.c source/env/env_set.c source/env/env_set_main.c source/env/env_append_val.c source/env/env_update.c source/env/env_basevars.c source/var/var_parse.c test/msh/env/env_unittest.c lib/libft/libft.a && ./a.out
	rm a.out
