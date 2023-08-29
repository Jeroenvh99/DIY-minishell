/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 13:15:11 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/29 13:57:49 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_prompt.h"
#include "msh_expand.h"
#include "msh_error.h"

#include "ft_string.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	heredoc(char const *delim, int fd, t_msh *msh)
{
	char	*line;
	t_errno	errno;

	signal(SIGINT, SIG_DFL);
	line = readline(PROMPT_CONT);
	while (line && ft_strncmp(line, delim, -1) != 0)
	{
		errno = expand(NULL, &line, msh);
		if (errno != MSH_SUCCESS)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline(PROMPT_CONT);
	}
	free(line);
	exit(errno);
}
