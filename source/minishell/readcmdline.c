/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readcmdline.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/12 17:34:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_parse.h"
#include "msh_utils.h"

#include "ft_list.h"
#include "ft_string.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static t_errno	rcmdl_add(t_list **tokens, char **line, char const *prompt);
static t_errno	rcmdl_strjoin(char **line, char *segment);

t_errno	readcmdline(t_list **tokens)
{
	char	*line;
	t_errno	errno;

	line = NULL;
	errno = rcmdl_add(tokens, &line, PROMPT);
	if (errno == MSH_NOCMDLINE || errno == MSH_MEMFAIL)
		return (free(line), list_clear(tokens, (t_freef)token_free), errno);
	add_history(line);
	free(line);
	return (errno);
}

static t_errno	rcmdl_add(t_list **tokens, char **line, char const *prompt)
{
	char	*segment;
	t_errno	errno;

	segment = readline(prompt);
	if (segment == NULL)
		return (MSH_NOCMDLINE);
	errno = lex(tokens, segment);
	if (rcmdl_strjoin(line, segment) == MSH_MEMFAIL)
		return (MSH_MEMFAIL);
	if (errno == MSH_MEMFAIL)
		return (errno);
	if (errno == MSH_INCOMPLETE_TOKEN)
		return (rcmdl_add(tokens, line, PROMPT_QUOTE));
	if (((t_token *)list_last(*tokens)->content)->type == TOK_PIPE)
		return (rcmdl_add(tokens, line, PROMPT_PIPE));
	return (errno);
}

static t_errno	rcmdl_strjoin(char **line, char *segment)
{
	char	*old_line;

	if (!*line)
	{
		*line = segment;
		return (MSH_SUCCESS);
	}
	old_line = *line;
	*line = ft_strjoin(old_line, segment);
	free(old_line);
	free(segment);
	if (*line == NULL)
		return (MSH_MEMFAIL);
	return (MSH_SUCCESS);
}