/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline_prompt.c                                   :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 12:46:33 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_prompt.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

t_errno	cmdline_prompt(char **line, t_msh *msh)
{
	t_fd			pipefd[2];
	int				exstat;
	t_errno const	ret[N_IACTV_EXIT] = {
		MSH_SUCCESS, MSH_GENERIC, 0, MSH_GENERIC, MSH_EOF};

	if (pipe(pipefd) == -1)
		return (msh_perror(0), MSH_PIPEFAIL);
	exstat = prompt(cmdline, pipefd[PIPE_WRITE], NULL, msh);
	while (exstat == IACTV_INTERRUPT || exstat == IACTV_FAIL)
		exstat = prompt(cmdline, pipefd[PIPE_WRITE], NULL, msh);
	close(pipefd[PIPE_WRITE]);
	if (exstat == IACTV_SUCCESS)
	{
		*line = ft_getline(pipefd[PIPE_READ]);
		if (!line)
			return (close(pipefd[PIPE_READ]), MSH_MEMFAIL);
	}
	return (close(pipefd[PIPE_READ]), ret[exstat]);
}
