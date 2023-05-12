/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 15:15:21 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_parse.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_hash.h"
#include "ft_list.h"
#include "ft_stdlib.h"

#include "msh_debug.h"
#include <stdio.h>

static t_errno	msh_loop(t_msh *msh);
static t_errno	msh_init(t_msh *msh, int argc, char **argv, char **envp);
static void		msh_deinit(t_msh *msh);
static void		cmd_free_wrapper(void *cmd);

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	msh.errno = msh_init(&msh, argc, argv, envp);
	if (msh.errno != MSH_SUCCESS)
		return (msh.errno);
	msh.errno = msh_loop(&msh);
	msh_deinit(&msh);
	return (msh.errno);
}

//add an errno check at the beginning of every function contained within the loop

static t_errno	msh_loop(t_msh *msh)
{
	t_list	*tokens;
	t_cmd	*cmd;

	tokens = NULL;
	while (msh->errno == MSH_SUCCESS)
	{
		msh->errno = readcmdline(&tokens, PROMPT);
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (cmd == NULL || list_append_ptr(&msh->cmds, cmd) != MSH_SUCCESS)
			return (MSH_MEMFAIL);
		msh->errno = parse(msh, &tokens);
		printf("Parser done! (exit: %d)\n", msh->errno);
		cmds_view(msh->cmds);
		list_clear(&msh->cmds, cmd_free_wrapper);
	}
	return (msh->errno);
}

static t_errno	msh_init(t_msh *msh, int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	//msh.env = env_copy(envp);
	msh->env = NULL;
	msh->var = hashtable_init(250, NULL);
	if (msh->var == NULL)
		return (MSH_MEMFAIL);
	msh->cmds = NULL;
	msh->exit = 0;
	return (MSH_SUCCESS);
}

static void	msh_deinit(t_msh *msh)
{
	(void) msh;
	//free env
	//free var
	//cleanup cmds
}

static void	cmd_free_wrapper(void *cmd)
{
	cmd_free(cmd);
}
