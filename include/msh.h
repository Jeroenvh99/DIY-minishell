/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:51:16 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/08 14:32:42 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "msh_error.h"
# include "msh_env.h"

# include "ft_hash.h"
# include "ft_list.h"
# include <stddef.h>
# include <sys/types.h>

# define PROMPT			"msh$ "
# define PROMPT_CONT	"> "
# define PROMPT_PIPE	"pipe> "
# define PROMPT_QUOTE	"dquote> "

typedef struct s_msh		t_msh;
typedef struct s_cmd		t_cmd;
typedef struct s_cmdtree	t_cmdtree;
typedef void				(*t_handler)(int);
typedef int					t_fd;

enum e_io {
	IO_IN = 0,
	IO_OUT,
	IO_ERR,
	N_IO,
};

enum e_treeop {
	TREE_OP_NONE = 0,
	TREE_OP_AND,
	TREE_OP_OR,
	TREE_OP_OPENPAR,
	TREE_OP_CLOSEPAR,
	N_TREE_OP,
};

enum e_treebranch {
	TREE_LEFT = 0,
	TREE_RIGHT,
};

/* Global shell data structure.
 * @param exit		The exit status of the most recently executed pipe.
 * @param child		The PID of the current child process.
 */
struct s_g_msh {
	int		exit;
	pid_t	child;
};

/* Shell data object.
 * @param g_msh	Global portion of shell data:
 * @param env	The shell environment.
 * @param tree	The current command queue.
 * @param errno	The current error code.
 */
struct s_msh {
	struct s_g_msh	*g_msh;
	t_env			env;
	t_cmdtree		*tree;
	t_errno			errno;
};

/* Command tree object.
 * @param pipeline	The command pipeline.
 * @param branches	The left and right-hand nodes.
 * @param parent	The parent node.
 * @param op		The operation to be performed
 * NOTE: A node will only have branches if its `op` member has been set to a
 * non-NULL value.
 */
struct s_cmdtree {
	union u_data {
		t_list				*pipeline;
		struct s_cmdtree	*branches[2];
	} data;
	struct s_cmdtree		*parent;
	int						op;
};

/* Simple command object.
 * @param path	The path to the executable (or the name of the builtin).
 * @param argc	The number of arguments supplied.
 * @param argv	The values of the command arguments.
 * @param io	Data pertaining to I/O processing.
 * @param sub	Whether the command is to be executed in a subshell.
 */
struct s_cmd {
	size_t	argc;
	union u_argv {
		t_list	*list;
		char	**array;
	} argv;
	t_fd	io[N_IO];
	int		subsh;
};

/* Base functions. */
void		msh_loop(t_msh *msh);
t_errno		readcmdline(t_list **tokens);
void		heredoc(char const *delim, int fd, t_msh *msh);
void		msh_deinit(t_msh *msh);

/* Command tree functions. */
t_cmdtree	*cmdtree_init(t_cmdtree *parent);
void		cmdtree_free(t_cmdtree *tree);

/* Command functions. */
t_cmd		*cmd_init(size_t argc, char **argv);
void		cmd_free(t_cmd *cmd);
void		cmd_free_wrapper(void *cmd);
void		cmd_free_list(t_cmd *cmd);
void		cmd_destroy(t_cmd **cmd);

/* Signal functions. */
void		handler_set(int signum, t_handler handler);
void		handle_sigint(int signum);
void		handle_sigint_heredoc(int signum);
void		handle_relay(int signum);

#endif
