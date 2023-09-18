/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subsh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:25:49 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/15 14:45:07 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

#include <stdlib.h>

/**
 * @brief	Execute a command inside a subshell.
 * @return	This function never returns.
 */
void	execute_subsh(t_cmd *cmd, t_msh *msh)
{
	if (execute_cmd(cmd, msh) != MSH_SUCCESS)
		msh->exit = EXIT_FAILURE;
	cmd_free(cmd);
	msh_deinit(msh);
	exit(msh->exit);
}
