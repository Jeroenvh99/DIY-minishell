/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:51:16 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/18 14:41:42 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "msh_error.h"
# include "msh_env.h"
# include "msh_utils.h"

# include "ft_list.h"
# include <limits.h>
# include <stddef.h>
# include <sys/types.h>

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

enum e_branch {
	TREE_LEFT,
	TREE_RIGHT,
};

enum e_treeop {
	TREE_OP_NONE = 0,
	TREE_OP_AND,
	TREE_OP_OR,
	TREE_OP_OPENPAR,
	TREE_OP_CLOSEPAR,
	N_TREE_OP,
};

enum e_pipeends {
	PIPE_READ = 0,
	PIPE_WRITE,
};

/* Shell data object.
 * @param g_msh	Global portion of shell data:
 * @param env	The shell environment.
 * @param var	The shell's local variables. ## UPCOMING ##
 * @param cmds	The current command queue.
 * @param errno	The current error code.
 */
struct s_msh {
	t_cmdtree	*tree;
	pid_t		child;
	t_env		env;
	char		cwd[PATH_MAX];
	t_errno		errno;
	int			exit;
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
 */
struct s_cmd {
	size_t	argc;
	union u_argv {
		t_list	*list;
		char	**array;
	} argv;
	t_fd	io[N_IO];
};

/* Base functions. */
void		msh_loop(t_msh *msh);
t_errno		cmdline_prompt(char **line, t_msh *msh);
t_errno		heredoc_read(int *fd, char const *delim, t_msh *msh);
void		msh_deinit(t_msh *msh);

/* Command tree functions. */
t_cmdtree	*cmdtree_init(t_cmdtree *parent);
void		cmdtree_destroy(t_cmdtree **tree);
void		cmdtree_free(t_cmdtree *tree);

/* Command functions. */
t_cmd		*cmd_init(size_t argc, char **argv);
void		cmd_free(t_cmd *cmd);
void		cmd_free_wrapper(void *cmd);
void		cmd_free_list(t_cmd *cmd);
void		cmd_destroy(t_cmd **cmd);

/* Signal functions. */
void		handler_set(int signum, t_handler handler);

#endif
