/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_exec.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:30:11 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/20 14:32:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTE_H
# define MSH_EXECUTE_H

# include "msh.h"
# include "msh_error.h"

# include <stddef.h>

enum e_builtins {
	BUILTIN_CD = 0,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_PWD,
	BUILTIN_UNSET,
	N_BUILTIN,
};

typedef int	(t_builtinf)(int, char const **, char const **);

t_errno	execute(t_list **pipeline, t_msh *msh); // Change pipeline to cmdtree.
t_errno	execute_pipeline(t_list **pipeline, t_msh *msh);
t_errno	execute_cmd(t_cmd *cmd, t_msh *msh);

/* Builtin functions. */
int		msh_cd(t_cmd *cmd, t_msh *msh);
int		msh_echo(t_cmd *cmd, t_msh *msh);
int		msh_env(t_cmd *cmd, t_msh *msh);
int		msh_exit(t_cmd *cmd, t_msh *msh);
int		msh_export(t_cmd *cmd, t_msh *msh);
int		msh_pwd(t_cmd *cmd, t_msh *msh);
int		msh_unset(t_cmd *cmd, t_msh *msh);

#endif
