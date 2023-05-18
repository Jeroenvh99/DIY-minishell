/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_out.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/15 17:30:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_expand.h"
#include "msh_utils.h"

#include <fcntl.h>
#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

t_errno	parse_output(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	char	*path;
	t_errno	errno;

	token_free(list_pop_ptr(tokens));
	path = NULL;
	errno = parse_iofile(&path, tokens, msh);
	if (errno != MSH_SUCCESS)
		return (free(path), errno);
	close(cmd->io.out);
	cmd->io.out = open(path, O_WRONLY | O_CREAT);
	free(path);
	if (cmd->io.out == -1)
		return (MSH_FILEFAIL);
	return (MSH_SUCCESS);
}

t_errno	parse_output_append(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	char	*path;
	t_errno	errno;

	token_free(list_pop_ptr(tokens));
	path = NULL;
	errno = parse_iofile(&path, tokens, msh);
	if (errno != MSH_SUCCESS)
		return (free(path), errno);
	close(cmd->io.out);
	cmd->io.out = open(path, O_WRONLY | O_CREAT | O_APPEND);
	free(path);
	if (cmd->io.out == -1)
		return (MSH_FILEFAIL);
	return (MSH_SUCCESS);
}
