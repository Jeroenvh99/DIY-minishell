/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/06/05 18:03:06 by dbasting      ########   odam.nl         */
=======
/*   Updated: 2023/06/07 22:54:16 by dbasting      ########   odam.nl         */
>>>>>>> 1359a19b93be50313859d4673d79c3da65b29344
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_env.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_hash.h"
#include "ft_stdio.h"
#include <stdlib.h>

<<<<<<< HEAD
#include "msh_debug.h"
#include <stdio.h>

static t_errno	msh_loop(t_msh *msh);
=======
>>>>>>> 1359a19b93be50313859d4673d79c3da65b29344
static t_errno	msh_init(t_msh *msh, int argc, char **argv, char **envp);

struct s_g_msh	g_msh = {.exit = 0, .child = 0};

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	msh.errno = msh_init(&msh, argc, argv, envp);
	if (msh.errno != MSH_SUCCESS)
		return (msh.errno);
	msh_loop(&msh);
	msh_deinit(&msh);
	ft_printf("Goodbye! (%d)\n", msh.errno);
	return (msh.errno);
}

void	msh_deinit(t_msh *msh)
{
	env_free(&msh->env);
	hashtable_destroy(&msh->var, free);
	list_clear(&msh->cmds, (t_freef)cmd_free);
}

static t_errno	msh_init(t_msh *msh, int argc, char **argv, char **envp)
{
	t_errno	errno;

	(void) argc;
	(void) argv;
	msh->g_msh = &g_msh;
	errno = env_init(&msh->env, envp);
	if (errno != MSH_SUCCESS)
		return (errno);
	msh->var = hashtable_init(100, NULL);
	if (msh->var == NULL)
		return (env_free(&msh->env), MSH_MEMFAIL);
	msh->cmds = NULL;
	msh->exit = 0;
	return (MSH_SUCCESS);
}
