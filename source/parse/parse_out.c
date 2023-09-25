/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_out.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 11:59:06 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_expand.h"
#include "list_utils.h"

#include <fcntl.h>
#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

/* Parse output: open a file (creating it if necessary) and assign its
 * descriptor to `cmd`. Preexisting files are closed.
 */
t_errno	parse_output(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	char	*path;
	t_errno	errno;

	token_free(list_pop_ptr(tokens));
	errno = parse_iofile(&path, tokens, msh);
	if (errno != MSH_SUCCESS)
		return (errno);
	close(cmd->io[IO_OUT]);
	cmd->io[IO_OUT] = open(path, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	free(path);
	if (cmd->io[IO_OUT] == -1)
		return (MSH_FILEFAIL);
	return (MSH_SUCCESS);
}

/* Parse output: open a file in append mode and assign its descriptor to `cmd`.
 * Preexisting files are closed.
 */
t_errno	parse_output_append(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	char	*path;
	t_errno	errno;

	token_free(list_pop_ptr(tokens));
	errno = parse_iofile(&path, tokens, msh);
	if (errno != MSH_SUCCESS)
		return (errno);
	close(cmd->io[IO_OUT]);
	cmd->io[IO_OUT] = open(path, O_WRONLY | O_CREAT | O_APPEND, 00644);
	free(path);
	if (cmd->io[IO_OUT] == -1)
		return (MSH_FILEFAIL);
	return (MSH_SUCCESS);
}
