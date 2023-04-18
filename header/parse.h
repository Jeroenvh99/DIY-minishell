/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:46:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/18 13:58:50 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "msh.h"

# define PROMPT	"msh$ "

typedef struct s_cmd {
	char	*name;
	char	**opt;
}	t_cmd;

typedef struct s_io {
	t_fd	in;
	t_fd	out;
	t_fd	err;
}	t_io;

typedef struct s_cmd_table {
	t_cmd	*cmds;
	t_io	io;
}	t_cmd_table;

#endif
