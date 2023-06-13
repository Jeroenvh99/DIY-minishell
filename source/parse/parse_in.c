/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/13 15:25:52 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include <fcntl.h>
#include "ft_list.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static t_errno	open_heredoc(int *fd, char const *delim, t_msh *msh);

t_errno	parse_input(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	char	*path;
	t_errno	errno;

	token_free(list_pop_ptr(tokens));
	errno = parse_iofile(&path, tokens, msh);
	if (errno != MSH_SUCCESS)
		return (errno);
	close(cmd->io.in);
	cmd->io.in = open(path, O_RDONLY);
	free(path);
	if (cmd->io.in < 0)
		return (MSH_FILEFAIL);
	return (MSH_SUCCESS);
}

t_errno	parse_heredoc(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	t_errno	errno;
	char	*delim;

	token_free(list_pop_ptr(tokens));
	delim = token_to_str(list_pop_ptr(tokens));
	if (delim == NULL)
		return (MSH_SYNTAX_ERROR);
	close(cmd->io.in);
	errno = open_heredoc(&cmd->io.in, delim, msh);
	free(delim);
	return (errno);
}

static t_errno	open_heredoc(int *fd, char const *delim, t_msh *msh)
{
	int		pipefd[2];
	pid_t	child;
	int		wstatus;

	*fd = -1;
	handler_set(SIGINT, handle_sigint_heredoc);
	if (pipe(pipefd) != 0)
		return (MSH_PIPEFAIL);
	child = fork();
	if (child == -1)
		return (MSH_FORKFAIL);
	if (child == 0)
		heredoc(delim, pipefd[PIPE_WRITE], msh);
	waitpid(child, &wstatus, WUNTRACED);
	close(pipefd[PIPE_WRITE]);
	*fd = pipefd[PIPE_READ];
	if (WIFSIGNALED(wstatus))
		return (MSH_NOCMDLINE);
	return (WEXITSTATUS(wstatus));
}
