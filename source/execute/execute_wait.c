/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:10:01 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/15 13:37:37 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief	Wait for the child process stored in msh->child. Other children are
			also waited for, but their return status is disregarded.
 * @return	The child's exit status or, if the child was terminated by way of a
 * 			signal: the signal number incremented by 128.
 */
int	execute_wait(t_msh *msh)
{
	int	wstatus;

	while (waitpid(-1, &wstatus, 0) != msh->child)
		;
	msh->child = 0;
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus) + 128);
	return (WEXITSTATUS(wstatus));
}

/**
 * @brief	Wait for the execution of a pipeline to finish.
 * @return	The exit status of the most recently launched child (i.e. the
 * 			rightmost command within the pipeline) or, this child was terminated
 * 			by way of a signal: the signal number incremented by 128.
 */
int	execute_wait_pipeline(pid_t *pidv, size_t n, t_msh *msh)
{
	msh->child = pidv[n - 1];
	return (execute_wait(msh));
}
