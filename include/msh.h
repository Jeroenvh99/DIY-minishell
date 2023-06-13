/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:51:16 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/13 15:27:23 by dbasting      ########   odam.nl         */
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

typedef enum e_in_mode {
	IN_STD,
	IN_REDIRECT,
	IN_HEREDOC,
	N_IN_MODE,
}	t_in_mode;

typedef enum e_out_mode {
	OUT_STD,
	OUT_REDIRECT,
	OUT_APPEND,
	N_OUT_MODE,
}	t_out_mode;

typedef void	(*t_handler)(int);
typedef int		t_fd;

enum e_pipeends {
	PIPE_READ = 0,
	PIPE_WRITE,
};

/* I/O information.
 * @param in	The file descriptor used for input.
 * @param out	The file descriptor used for output.
 * @param err	The file descriptor used for errors.
 */
typedef struct s_io {
	t_fd	in;
	t_fd	out;
	t_fd	err;
}	t_io;

/* Simple command object.
 * @param path	The path to the executable (or the name of the builtin).
 * @param argc	The number of arguments supplied.
 * @param argv	The values of the command arguments.
 * @param io	Data pertaining to I/O processing.
 */
typedef struct s_cmd {
	size_t	argc;
	union u_argv {
		t_list	*list;
		char	**array;
	} argv;
	t_io	io;
}	t_cmd;

/* Command tree object.
 * @param pipeline	The command pipeline.
 * @param branches	The left and right-hand nodes.
 * @param parent	The parent node.
 * @param op		The operation to be performed
 * NOTE: A node will only have branches if its `op` member has been set to a
 * non-NULL value.
 */
typedef struct s_cmdtree {
	union u_data {
		t_list				*pipeline;
		struct s_cmdtree	*branches[2];
	} data;
	struct s_cmdtree		*parent;
	int						op;
}	t_cmdtree;

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
 * @param var	The shell's local variables. ## UPCOMING ##
 * @param cmds	The current command queue.
 * @param errno	The current error code.
 */
typedef struct s_msh {
	struct s_g_msh	*g_msh;
	t_env			env;
	t_hashtable		*var;
	t_list			*cmds;
	int				exit;
	t_errno			errno;
}	t_msh;

/* Base functions. */
void	msh_loop(t_msh *msh);
t_errno	readcmdline(t_list **tokens);
void	heredoc(char const *delim, int fd, t_msh *msh);
void	msh_deinit(t_msh *msh);

/* Command functions. */
t_cmd	*cmd_init(size_t argc, char **argv);
t_errno	cmd_finish(t_cmd *cmd);
void	cmd_free(t_cmd *cmd);
void	cmd_free_wrapper(void *cmd);
void	cmd_free_list(t_cmd *cmd);
void	cmd_destroy(t_cmd **cmd);

/* Signal functions. */
void	handler_set(int signum, t_handler handler);
void	handle_sigint(int signum);
void	handle_sigint_heredoc(int signum);
void	handle_sigint_relay(int signum);

/* Builtin functions. */ /* Moet dit niet naar msh_exec.h? */
int		msh_cd(t_cmd *cmd, t_msh *msh);
int		msh_echo(t_cmd *cmd, t_msh *msh);
int		msh_env(t_cmd *cmd, t_msh *msh);
int		msh_exit(t_cmd *cmd, t_msh *msh);
int		msh_export(t_cmd *cmd, t_msh *msh);
int		msh_pwd(t_cmd *cmd, t_msh *msh);
int		msh_unset(t_cmd *cmd, t_msh *msh);

#endif
