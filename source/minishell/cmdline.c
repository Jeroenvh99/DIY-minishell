/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:13:15 by dbasting          #+#    #+#             */  
/*   Updated: 2023/09/05 11:42:19 by dbasting         ###   ########.fr       */
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
	if (exstat == IACTV_SUCCESS)
	{
		write(outf, line, ft_strlen(line));
		free(line);
	}
	close(outf);
	exit(exstat);
}

static int	cmdl_read(char **line)
{
	int		params[N_PARAMS];
	int		syntax_check;

	ft_memset(params, 0x0, sizeof(int) * N_PARAMS);
	if (cmdl_readline(line, params) == IACTV_FAIL)
		return (IACTV_FAIL);
	syntax_check = syntax(*line, params);
	while (syntax_check != SYNTAX_SUCCESS)
	{
		if (syntax_check == SYNTAX_FATAL)
			return (msh_strerror(MSH_SYNTAX_ERROR), IACTV_FAIL);
		if (cmdl_readline(line, params) == IACTV_FAIL)
			return (IACTV_FAIL);
		ft_memset(params, 0x0, sizeof(int) * N_PARAMS);
		syntax_check = syntax(*line, params);
	}
	return (IACTV_SUCCESS);
}

static int	cmdl_readline(char **line, int params[N_PARAMS])
{
	char	pbuf[PBUFSIZE];
	char	*segment;

	cmdl_rl_prompt(pbuf, params);
	segment = readline(pbuf);
	if (!segment)
		exit(IACTV_EOF);
	if (cmdl_strjoin(line, segment) != 0)
		return (IACTV_FAIL);
	return (IACTV_SUCCESS);
}

static void	cmdl_rl_prompt(char pbuf[PBUFSIZE], int params[N_PARAMS])
{
	char const *const	operatorp[3] = {
		PROMPT_PIPE, PROMPT_CMDAND, PROMPT_CMDOR};
	char const *const	quotep[2] = {
		PROMPT_QUOTE, PROMPT_DQUOTE};

	pbuf[0] = '\0';
	if (params[OPERATOR] != TOK_NONE)
		ft_strlcat(pbuf, operatorp[params[OPERATOR] - TOK_PIPE], PBUFSIZE);
	if (params[PARNS] > 0)
		ft_strlcat(pbuf, PROMPT_PAR, PBUFSIZE);
	ft_strlcat(pbuf, quotep[params[QUOTE] - SQUOTE], PBUFSIZE);
	if (pbuf[0] != '\0')
		ft_strlcat(pbuf, PROMPT_CONT, PBUFSIZE);
	else
		ft_strlcat(pbuf, PROMPT, PBUFSIZE);
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
	if (*line == NULL)
		return (free(segment), 1);
	free(segment);
	return (0);
}
