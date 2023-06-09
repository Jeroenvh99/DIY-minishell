/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:49:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/09 14:59:01 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_parse.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <signal.h>

#include "msh_debug.h"

typedef void	(*t_handler)(int);

static void	handler_set(t_handler handler);

void	msh_loop(t_msh *msh)
{
	t_list	*tokens;

	tokens = NULL;
	while (1)
	{
		handler_set(handle_sigint);
		msh->errno = readcmdline(&tokens);
		if (msh->errno == MSH_NOCMDLINE)
		{
			msh->errno = MSH_SUCCESS;
			break ;
		}
		msh->errno = parse(msh, &tokens);
		if (msh->errno != MSH_SUCCESS)
			msh_strerror(msh->errno);
		else
		{
			handler_set(handle_sigint_relay);
			cmds_view(msh->cmds); //insert executor here
		}
		list_clear(&msh->cmds, (t_freef)cmd_free);
	}
}

static void	handler_set(t_handler handler)
{
	struct sigaction const	act = {.sa_handler = handler};

	sigaction(SIGINT, &act, NULL);
}
