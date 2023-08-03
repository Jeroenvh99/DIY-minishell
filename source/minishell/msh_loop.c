/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:49:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/03 21:37:39 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_execute.h"
#include "msh_parse.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <unistd.h>

void	msh_loop(t_msh *msh)
{
	t_list	*tokens;

	tokens = NULL;
	while (1)
	{
		handler_set(SIGINT, handle_sigint);
		handler_set(SIGQUIT, SIG_IGN);
		msh->errno = readcmdline(&tokens);
		if (msh->errno == MSH_NOCMDLINE)
		{
			msh->errno = MSH_SUCCESS;
			break ;
		}
		msh->errno = parse(msh, &tokens);
		if (msh->errno == MSH_SUCCESS)
			msh->errno = execute(&msh->cmds, msh);
		list_clear(&msh->cmds, (t_freef)cmd_free);
		if (msh->errno >= MSH_GENERIC)
			msh_strerror(msh->errno);
	}
}
