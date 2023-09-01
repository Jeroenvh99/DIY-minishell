/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:13:15 by dbasting          #+#    #+#             */  
/*   Updated: 2023/09/01 14:41:53 by dbasting         ###   ########.fr       */
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
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	cmdl_add(t_list **tokens, char **line, char const *prompt);
static int	cmdl_strjoin(char **line, char *segment);

void	cmdline(t_fd outf, char const *delim, t_msh *msh)
{
	char	*line;
	int		exstat;
	t_list	*tokens;

	(void) delim;
	(void) msh;
	handler_set(SIGINT, SIG_DFL);
	tokens = NULL;
	line = NULL;
	exstat = cmdl_add(&tokens, &line, PROMPT);
	if (exstat == IACTV_EOF)
	{
		list_clear(&tokens, (t_freef)token_free);
		free(line);
		close(outf);
		exit(exstat);
	}
	handler_set(SIGINT, SIG_IGN);
	write(outf, line, ft_strlen(line));
	close(outf);
	list_clear(&tokens, (t_freef)token_free);
	free(line);
	exit(exstat);
}

static int	cmdl_add(t_list **tokens, char **line, char const *prompt)
{
	char *const	segment = readline(prompt);
	t_errno		errno;
	int			syntcheck;

	if (!segment)
		return (IACTV_EOF);
	errno = lex(tokens, segment);
	if (errno == MSH_MEMFAIL || cmdl_strjoin(line, segment) == MSH_MEMFAIL)
		return (IACTV_FAILED);
	if (errno == MSH_INCOMPLETE_TOKEN)
		return (cmdl_add(tokens, line, PROMPT_QUOTE PROMPT_CONT));
	syntcheck = syntax_check(*tokens);
	if (syntcheck == SYNTERROR_FATAL)
		return (IACTV_FAILED);
	if (syntcheck > SYNTERROR_FATAL)
		return (cmdl_add(tokens, line, PROMPT_CONT));
	return (errno);
}

static int	cmdl_strjoin(char **line, char *segment)
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
