/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:51:16 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 17:51:17 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "msh_error.h"

# include "ft_hash.h"
# include "ft_list.h"
# include <stddef.h>

# define PROMPT			"msh$ "
# define PROMPT_CONT	"> "
# define PROMPT_PIPE	"pipe> "

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

typedef int	t_fd;

typedef union u_file {
	char	*name;
	t_fd	fd;
}	t_file;

/* I/O information.
 * @param in		The name of the file used for input.
 * @param out		The name of the file used for output.
 * @param err		The name of the file used for errors.
 * @param in_mode	The mode in which the input stream is redirected.
 * @param out_mode	The mode in which the output stream is redirected.
 * @param err_mode	The mode in which the error stream is redirected.
 */
typedef struct s_io {
	t_file		in;
	t_file		out;
	t_file		err;
	t_in_mode	in_mode;
	t_out_mode	out_mode;
	t_out_mode	err_mode;
}	t_io;

/* Simple command object.
 * @param path	The path to the executable (or the name of the builtin).
 * @param argc	The number of arguments supplied.
 * @param argv	The values of the command arguments.
 * @param io	Data pertaining to I/O processing.
 */
typedef struct s_cmd {
	size_t	argc;
	char	**argv;
	t_io	io;
}	t_cmd;

/* Shell data object.
 * @param env	The shell environment.
 * @param var	The shell's local variables.
 * @param cmds	The current command queue.
 * @param exit	The exit status of the most recently executed foreground pipe.
 * @param errno	The current error code.
 */
typedef struct s_msh {
	char		**env;
	t_hashtable	*var;
	t_list		*cmds;
	int			exit;
	t_errno		errno;
}	t_msh;

t_errno		readcmdline(t_list **token_list, char const *prompt);

// Command functions.
t_cmd		*cmd_init(size_t argc, char **argv);
void		cmd_free(t_cmd *cmd);
void		cmd_destroy(t_cmd **cmd);

#endif
