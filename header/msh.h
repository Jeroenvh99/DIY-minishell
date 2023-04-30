/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:51:16 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/18 13:51:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include "msh_error.h"

# include "ft_list.h"
# include <stddef.h>

# define PROMPT			"msh$ "
# define PROMPT_CONT	"> "

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

/* Variable object.
 * @param name	The variable's name.
 * @param value	The variable's value.
 */
typedef struct s_var {
	char *name;
	char *value;
}	t_var;

/* I/O information.
 * @param in		The name of the file used for input.
 * @param out		The name of the file used for output.
 * @param err		The name of the file used for errors.
 * @param in_mode	The mode in which the input stream is redirected.
 * @param out_mode	The mode in which the output stream is redirected.
 * @param err_mode	The mode in which the error stream is redirected.
 */
typedef struct s_io {
	char		*in;
	char		*out;
	char		*err;
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
	char	*path;
	size_t	argc;
	char	**argv;
	t_io	io;
}	t_cmd;

/* Command table object.
 * @param cmds	A linked list containing the simple commands that constitute
 * 				the command table.
 * @param io	The input-output information.
 */
typedef struct s_cmdtable {
	t_list	*cmds;
	t_io	io;
}	t_cmdtable;

t_cmdtable	*cmdtable_init(t_list *tokens);
void		cmdtable_destroy(t_cmdtable **cmdtable);
t_cmd		*cmd_init(char *path, size_t argc, char **argv);
void		cmd_destroy(t_cmd **cmd);

t_errno		input_get(t_list **token_list, char const *prompt);

#endif
