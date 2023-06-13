/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:49:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/13 14:39:28 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_parse.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <signal.h>

#include "msh_debug.h"

void	msh_loop(t_msh *msh)
{
	t_list	*tokens;

	tokens = NULL;
	while (1)
	{
		handler_set(SIGINT, handle_sigint);
		msh->errno = readcmdline(&tokens);
		if (msh->errno == MSH_NOCMDLINE)
		{
			msh->errno = MSH_SUCCESS;
			break ;
		}
		msh->errno = parse(msh, &tokens);
		if (msh->errno == MSH_SUCCESS)
		{
			handler_set(SIGINT, handle_sigint_relay);
			cmds_view(msh->cmds); //insert executor here
		}
		list_clear(&msh->cmds, (t_freef)cmd_free);
		if (msh->errno > MSH_NOCMDLINE)
			msh_strerror(msh->errno);
	}
}
