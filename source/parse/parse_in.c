/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_in.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/01 14:25:21 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include <fcntl.h>
#include "ft_list.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* Parse input tokens: open a file and assign its descriptor to `cmd`. 
 * Preexisting files are closed.
 */
t_errno	parse_input(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	char	*path;
	t_errno	errno;

	token_free(list_pop_ptr(tokens));
	errno = parse_iofile(&path, tokens, msh);
	if (errno != MSH_SUCCESS)
		return (errno);
	if (cmd->io[IO_IN] > STDERR_FILENO)
		close(cmd->io[IO_IN]);
	cmd->io[IO_IN] = open(path, O_RDONLY);
	free(path);
	if (cmd->io[IO_IN] < 0)
		return (MSH_FILEFAIL);
	return (MSH_SUCCESS);
}

/* Parse heredoc tokens: open a heredoc and assign its descriptor to `cmd`.
 * Preexisting files are closed.
 */
t_errno	parse_heredoc(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	t_errno	errno;
	char	*delim;

	token_free(list_pop_ptr(tokens));
	delim = token_to_str(list_pop_ptr(tokens));
	if (delim == NULL)
		return (MSH_SYNTAX_ERROR);
	if (cmd->io[IO_IN] > STDERR_FILENO)
		close(cmd->io[IO_IN]);
	errno = heredoc_read(&cmd->io[IO_IN], delim, msh);
	free(delim);
	return (errno);
}
