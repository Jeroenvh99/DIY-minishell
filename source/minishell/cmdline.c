/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:13:15 by dbasting          #+#    #+#             */  
/*   Updated: 2023/09/04 15:58:27 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_prompt.h"
#include "msh_error.h"
#include "msh_parse.h"
#include "msh_syntax.h"
#include "msh_utils.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#ifdef __APPLE__
# include <stdio.h>
#endif
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define PBUFSIZE	64

static int	cmdl_add(t_list **tokens, char **line, int syntax_params[N_PARAMS]);
static char	*cmdl_rl(int params[N_PARAMS]);
static int	cmdl_strjoin(char **line, char *segment);

void	cmdline(t_fd outf, char const *delim, t_msh *msh)
{
	char	*line;
	int		exstat;
	t_list	*tokens;
	int		syntax_params[N_PARAMS];

	(void) delim;
	(void) msh;
	handler_set(SIGINT, SIG_DFL);
	tokens = NULL;
	line = NULL;
	ft_memset(syntax_params, 0x0, sizeof(int) * N_PARAMS);
	exstat = cmdl_add(&tokens, &line, syntax_params);
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

static int	cmdl_add(t_list **tokens, char **line, int syntax_params[N_PARAMS])
{
	char *const	segment = cmdl_rl(syntax_params);

	if (!segment)
		return (IACTV_EOF);
	if (cmdl_strjoin(line, segment) != 0)
		return (IACTV_FAILED);
	if (syntax(*line, syntax_params) == SYNTAX_FATAL)
	{
		ft_dprintf(2, "msh: Syntax error!!!\n");
		return (IACTV_FAILED);
	}
	if (syntax_params[QUOTE] != NOQUOTE
		|| syntax_params[OPERATOR] != TOK_NONE
		|| syntax_params[PARNS] != 0)
		return (cmdl_add(tokens, line, syntax_params));
	return (IACTV_SUCCESS);
}

static char	*cmdl_rl(int params[N_PARAMS])
{
	char const *const	operatorp[3] = {
		PROMPT_PIPE, PROMPT_CMDAND, PROMPT_CMDOR};
	char const *const	quotep[2] = {
		PROMPT_QUOTE, PROMPT_DQUOTE};
	char				pbuf[PBUFSIZE];

	pbuf[0] = '\0';
	if (params[OPERATOR] == TOK_NONE && params[PARNS] == 0 && params[QUOTE] == NOQUOTE)
		return (readline(PROMPT));
	if (params[OPERATOR] != TOK_NONE)
		ft_strlcat(pbuf, operatorp[params[OPERATOR] - TOK_PIPE], PBUFSIZE);
	if (params[PARNS] > 0)
		ft_strlcat(pbuf, PROMPT_PAR, PBUFSIZE);
	if (params[QUOTE] != NOQUOTE)
		ft_strlcat(pbuf, quotep[params[OPERATOR]] - NOQUOTE, PBUFSIZE);
	ft_strlcat(pbuf, PROMPT_CONT, PBUFSIZE);
	return (readline(pbuf));
}

static int	cmdl_strjoin(char **line, char *segment)
{
	char	*old_line;

	if (!*line)
	{
		*line = segment;
		return (0);
	}
	old_line = *line;
	*line = ft_strjoin(old_line, segment);
	free(old_line);
	free(segment);
	if (*line == NULL)
		return (1);
	return (0);
}
