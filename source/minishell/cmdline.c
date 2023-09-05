/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#     #+#                */
/*   Updated: 2023/09/05 14:50:34 by dbasting      ########   odam.nl         */
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

static int	cmdl_read(char **line);
static int	cmdl_readline(char **line, int params[N_PARAMS]);
static void	cmdl_rl_prompt(char pbuf[PBUFSIZE], int params[N_PARAMS]);
static int	cmdl_strjoin(char **line, char *segment);

/**
 * @brief	Read a command line and write it to a pipe for the parent process
 * 			to read from.
 * @param	outf	The file descriptor to write to.
 * @exit	IATCV_SUCCESS	Success.
 * 			IACTV_FAIL		Fatal failure.
 * 			IACTV_EOF		End of file was encountered.
 */
void	cmdline(t_fd outf, char const *delim, t_msh *msh)
{
	char	*line;
	int		exstat;

	(void) delim;
	(void) msh;
	handler_set(SIGINT, SIG_DFL);
	line = NULL;
	exstat = cmdl_read(&line);
	handler_set(SIGINT, SIG_IGN);
	if (exstat == IACTV_SUCCESS || exstat == IACTV_FAIL_0)
	{
		write(outf, line, ft_strlen(line));
		free(line);
	}
	close(outf);
	exit(exstat);
}

/**
 * @brief	Gather a command line. The line may be spread out across several
 * 			lines (segments) for syntax-related reasons: these segments are
 * 			concatenated. No newlines are inserted.
 * @param	line	A pointer to the entire line.
 * @return	An exit status. Possible values:
 * 			IACTV_SUCCESS	Success.
 * 			IACTV_FAIL		Fatal failure.
 */
static int	cmdl_read(char **line)
{
	int		params[N_PARAMS];
	int		synterr;

	ft_memset(params, 0x0, sizeof(int) * N_PARAMS);
	if (cmdl_readline(line, params) == IACTV_FAIL)
		return (IACTV_FAIL);
	synterr = syntax(*line, params);
	while (synterr != SYNTAX_SUCCESS)
	{
		if (synterr == SYNTAX_FATAL)
			return (msh_strerror(MSH_SYNTAX_ERROR), IACTV_FAIL_0);
		if (cmdl_readline(line, params) == IACTV_FAIL)
			return (IACTV_FAIL);
		ft_memset(params, 0x0, sizeof(int) * N_PARAMS);
		synterr = syntax(*line, params);
	}
	return (IACTV_SUCCESS);
}

/**
 * @brief	Read a single command line segment through readline().
 * @param	line	A pointer to the command line read so far.
 * @param	params	The parameter array used to build the prompt.
 * @return	An exit status. Possible values:
 * 			IACTV_SUCCESS	Success.
 *			IACTV_FAIL		Fatal failure.
 * @note	If readline() encounters EOF, the process will exit(IACTV_EOF) from
 * 			within this function.
 */
static int	cmdl_readline(char **line, int params[N_PARAMS])
{
	char	pbuf[PBUFSIZE];
	char	*segment;

	cmdl_rl_prompt(pbuf, params);
	while (1)
	{
		segment = readline(pbuf);
		if (!segment)
			exit(IACTV_EOF);
		if (segment[0] != '\0')
			break ;
		free(segment);
	}
	if (cmdl_strjoin(line, segment) != 0)
		return (IACTV_FAIL);
	return (IACTV_SUCCESS);
}

static char const *const	g_opprompt[3] = {
	PROMPT_PIPE, PROMPT_CMDAND, PROMPT_CMDOR};
static char const *const	g_quoteprompt[2] = {
	PROMPT_QUOTE, PROMPT_DQUOTE};

/**
 * @brief	Write an appropriate line prompt. If there are no syntax errors to 
 * 			be amended, the prompt will be "msh$ ". Otherwise, it will comprise
 * 			one or more of the following indicators (in the listed order):
 * 				"pipe", "cmdor" or "cmdand", in case of an incomplete operator;
 * 				"parenthesis", if there's at least one set of parentheses that
 * 				must be closed;
 * 				"quote" or "dquote" if there's an unclosed single or double
 * 				quotation mark;
 * 			followed by "> ".
 * @param	pbuf	The buffer containing the prompt.
 * @param	params	The syntax check parameters.
 */
static void	cmdl_rl_prompt(char pbuf[PBUFSIZE], int params[N_PARAMS])
{
	pbuf[0] = '\0';
	if (params[OPERATOR] != TOK_NONE)
		ft_strlcat(pbuf, g_opprompt[params[OPERATOR] - TOK_PIPE], PBUFSIZE);
	if (params[PARNS] > 0)
		ft_strlcat(pbuf, PROMPT_PAR, PBUFSIZE);
	if (params[QUOTE] != NOQUOTE)
		ft_strlcat(pbuf, g_quoteprompt[params[QUOTE] - SQUOTE], PBUFSIZE);
	if (pbuf[0] != '\0')
		ft_strlcat(pbuf, PROMPT_CONT, PBUFSIZE);
	else
		ft_strlcat(pbuf, PROMPT, PBUFSIZE);
}

/**
 * @brief	Append a line segment to the total line and dispose of it.
 */
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
	if (*line == NULL)
		return (free(segment), 1);
	free(segment);
	return (0);
}
