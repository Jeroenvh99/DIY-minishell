/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline_prompt.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/29 14:58:08 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_prompt.h"
#include "msh_error.h"
#include "msh_parse.h"
#include "msh_syntax.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_string.h"
#ifdef __APPLE__
# include <stdio.h>
#endif
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static int	cmdlp_add(t_list **tokens, char **line, char const *prompt);
static int	cmdlp_strjoin(char **line, char *segment);

void	cmdline_prompt(t_fd outf)
{
	char	*line;
	int		exstat;
	t_list	*tokens;

	tokens = NULL;
	handler_set(SIGINT, SIG_DFL);
	line = NULL;
	exstat = cmdlp_add(&tokens, &line, PROMPT);
	if (exstat == IACTV_EOF)
	{
		list_clear(&tokens, (t_freef)token_free);
		free(line);
		exit(exstat);
	}
	handler_set(SIGINT, SIG_IGN);
	write(outf, line, ft_strlen(line));
	list_clear(&tokens, (t_freef)token_free);
	free(line);
	exit(exstat);
}

static int	cmdlp_add(t_list **tokens, char **line, char const *prompt)
{
	char *const	segment = readline(prompt);
	t_errno		errno;
	int			syntcheck;

	if (!segment)
		return (IACTV_EOF);
	errno = lex(tokens, segment);
	if (!tokens)
		return (MSH_NOCMDLINE);
	if (cmdlp_strjoin(line, segment) == MSH_MEMFAIL)
		return (IACTV_FAILED);
	if (errno == MSH_MEMFAIL)
		return (errno);
	if (errno == MSH_INCOMPLETE_TOKEN)
		return (cmdlp_add(tokens, line, PROMPT_QUOTE PROMPT_CONT));
	syntcheck = syntax_check(*tokens);
	if (syntcheck == SYNTERROR_FATAL)
		return (MSH_SYNTAX_ERROR);
	if (syntcheck > SYNTERROR_FATAL)
		return (cmdlp_add(tokens, line, PROMPT_CONT));
	return (errno);
}

static int	cmdlp_strjoin(char **line, char *segment)
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
