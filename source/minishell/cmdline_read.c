/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline_read.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/29 15:22:19 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh_prompt.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#ifdef __APPLE__
# include <stdio.h>
#endif
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	cmdline_wait(t_fd pipefd[2]);

t_errno	cmdline_read(t_list **tokens)
{
	char	*line;
	t_fd	pipefd[2];
	int		exstat;
	int		errno;

	if (pipe(pipefd) == -1)
		return (msh_perror(0), MSH_PIPEFAIL);
	exstat = cmdline_wait(pipefd);
	while (exstat == IACTV_SIGNALED)
		exstat = cmdline_wait(pipefd);
	close(pipefd[PIPE_WRITE]);
	if (exstat == -1 || exstat == IACTV_FAILED)
		return (MSH_GENERIC);
	if (exstat == IACTV_EOF)
		return (close(pipefd[PIPE_READ]), MSH_NOCMDLINE); 
	line = ft_getline(pipefd[PIPE_READ]);
	close(pipefd[PIPE_READ]);
	errno = lex(tokens, line);
	if (errno == MSH_SUCCESS)
		add_history(line);
	free(line);
	return (MSH_SUCCESS);
}

static int	cmdline_wait(t_fd pipefd[2])
{
	pid_t const	promptid = fork();
	int			wstat;

	if (promptid == -1)
		return (msh_perror(0), -1);
	if (promptid == 0)
		cmdline_prompt(pipefd[PIPE_WRITE]);
	waitpid(promptid, &wstat, 0);
	if (WIFSIGNALED(wstat))
	{
		handle_sigint(SIGINT);
		if (WTERMSIG(wstat) == SIGINT)
			return (IACTV_SIGNALED);
		return (IACTV_TERMINATED);
	}
	return (WEXITSTATUS(wstat));
}
