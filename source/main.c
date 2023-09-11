/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/11 16:05:37 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_env.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_hash.h"
#include "ft_stdio.h"
#include <signal.h>
#include <stdlib.h>

static t_errno	msh_init(t_msh *msh, int argc, char **argv, char **envp);

int	g_signum = -1;

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	handler_set(SIGINT, SIG_IGN);
	handler_set(SIGQUIT, SIG_IGN);
	msh.errno = msh_init(&msh, argc, argv, envp);
	if (msh.errno != MSH_SUCCESS)
		return (msh.errno);
	msh_loop(&msh);
	msh_deinit(&msh);
	ft_printf("exit\n");
	return (msh.errno);
}

void	msh_deinit(t_msh *msh)
{
	env_free(&msh->env);
	cmdtree_destroy(&msh->tree);
}

static t_errno	msh_init(t_msh *msh, int argc, char **argv, char **envp)
{
	t_errno	errno;

	(void) argc;
	(void) argv;
	msh->child = 0;
	msh->exit = 0;
	errno = env_init(&msh->env, envp);
	if (errno != MSH_SUCCESS)
		return (errno);
	msh->tree = NULL;
	return (MSH_SUCCESS);
}
