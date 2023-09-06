/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:44:02 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/04 23:39:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_prompt.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include <unistd.h>

/**
* @brief	Read from a here document.
*/
t_errno	heredoc_read(t_fd *fd, char const *delim, t_msh *msh)
{
	int				pipefd[2];
	int				exstat;
	t_errno const	ret[N_IACTV_EXIT] = {
		MSH_SUCCESS, MSH_GENERIC, MSH_EOF, MSH_GENERIC, MSH_SUCCESS};

	*fd = -1;
	if (pipe(pipefd) != 0)
		return (MSH_PIPEFAIL);
	exstat = prompt(heredoc, pipefd[PIPE_WRITE], delim, msh);
	close(pipefd[PIPE_WRITE]);
	*fd = pipefd[PIPE_READ];
	return (ret[exstat]);
}
