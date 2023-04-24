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

typedef int	t_fd

/* Variable object.
 * @param name	The variable's name.
 * @param value	The variable's value.
 */
typedef struct s_var {
	char *name;
	char *value;
}	t_var;

/* Simple command object.
 * @param name	The executable or builtin associated with the command.
 * @param opt	The command options.
 */
typedef struct s_cmd {
	char	*name;
	char	*path;
	char	**opts;
}	t_cmd;

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

#endif
