/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_execute.h                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:30:11 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/15 13:34:59 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTE_H
# define MSH_EXECUTE_H

# include "msh.h"
# include "msh_error.h"

# include <stddef.h>
# include <unistd.h>

enum e_builtins {
	BUILTIN_CD = 0,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET,
	N_BUILTIN,
};

typedef int	(*t_builtinf)(t_cmd *, t_msh *);

t_errno	execute(t_msh *msh);
t_errno	execute_cmdtree(t_cmdtree *tree, t_msh *msh);
t_errno	execute_pipeline(t_list **pipeline, t_msh *msh);
t_errno	execute_cmd(t_cmd *cmd, t_msh *msh);
t_errno	execute_bin(t_cmd *cmd, t_msh *msh);

void	execute_subsh(t_cmd *cmd, t_msh *msh);
int		execute_wait(t_msh *msh);
int		execute_wait_pipeline(pid_t *pidv, size_t n, t_msh *msh);

int		get_pathname(char *const buf, char const *filename, char const *path);

/* Builtin utilities. */
int		msh_cd(t_cmd *cmd, t_msh *msh);
int		msh_echo(t_cmd *cmd, t_msh *msh);
int		msh_env(t_cmd *cmd, t_msh *msh);
int		msh_exit(t_cmd *cmd, t_msh *msh);
int		msh_export(t_cmd *cmd, t_msh *msh);
int		msh_pwd(t_cmd *cmd, t_msh *msh);
int		msh_unset(t_cmd *cmd, t_msh *msh);

/* Builtin util functions. */
size_t	removecurdir(char *str, size_t i);
size_t	removeprevdir(char *str, size_t i);
void	removelastslash(char *str);
void	removeduplicateslash(char *str);

#endif
