/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/15 18:09:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_expand.h"
#include "msh_utils.h"

#include <fcntl.h>
#include "ft_string.h"
#include "ft_list.h"
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static int	read_heredoc(char const *delim, t_msh *msh);

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
	char	*delim;

	token_free(list_pop_ptr(tokens));
	delim = token_to_str(list_pop_ptr(tokens));
	if (delim == NULL)
		return (MSH_SYNTAX_ERROR);
	close(cmd->io.in);
	cmd->io.in = read_heredoc(delim, msh);
	free(delim);
	if (cmd->io.in == -1)
		return (MSH_FILEFAIL);
	return (MSH_SUCCESS);
}

static int	read_heredoc(char const *delim, t_msh *msh)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) != 0)
		return (-1);
	line = readline(PROMPT_CONT);
	while (line && ft_strncmp(line, delim, -1) != 0)
	{
		if (expand(NULL, &line, msh) != MSH_SUCCESS)
			return (free(line), close(fds[0]), close(fds[1]), -1);
		write(fds[0], line, ft_strlen(line));
		free(line);
		line = readline(PROMPT_CONT);
	}
	free(line);
	close(fds[0]);
	return (fds[1]);
}
