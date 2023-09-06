/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 13:15:11 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/04 23:40:06 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_prompt.h"
#include "msh_expand.h"
#include "msh_error.h"

#include "ft_stdio.h"
#include "ft_string.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static inline void	heredoc_eof(char const *delim);
static inline void	heredoc_write(t_fd outf, char **line, t_msh *msh);

void	heredoc(t_fd outf, char const *delim, t_msh *msh)
{
	char	*line;

	line = NULL;
	handler_set(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline(PROMPT_HEREDOC PROMPT_CONT);
		if (!line)
			heredoc_eof(delim);
		else if (ft_strncmp(line, delim, -1) == 0)
			break ;
		heredoc_write(outf, &line, msh);
		free(line);
	}
	free(line);
	exit(IACTV_SUCCESS);
}

static inline void	heredoc_eof(char const *delim)
{
	ft_dprintf(2, "msh: warning: here-document delimited by end-of-file "
		"(wanted `%s')\n", delim);
	exit(IACTV_SUCCESS);
}

static inline void	heredoc_write(t_fd outf, char **line, t_msh *msh)
{
	if (expand(NULL, line, msh) != MSH_SUCCESS)
	{
		msh_perror(0);
		exit(IACTV_FAIL);
	}
	write(outf, *line, ft_strlen(*line));
	write(outf, "\n", 1);
}
