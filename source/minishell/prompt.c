/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:10:06 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/04 23:39:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_prompt.h"
#include "msh_error.h"

#ifdef __APPLE__
# include <stdio.h>
#endif
#include "readline/readline.h"

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static inline void	newline(void);

/**
 * @brief	Create an interactive prompt to read input from.
 * @param	promptf	The prompt function (either cmdline or heredoc).
 * @param	outf	The file descriptor to which the prompt will write its
 * 					output.
 * @param	delim	The prompt will read input up to until it encounters this
 * 					delimiter. Supply NULL if the prompt should only read a
 * 					single line.
 * @param	msh		The msh data struct.
 * @return	A status code. Possible values:
 * 			IACTV_SUCCESS	Success.
 * 			IACTV_FAIL		The call to fork() failed, or a fatal error
 * 							occurred within the prompt.
 * 			IACTV_INTERRUPT	The prompt was terminated through SIGINT.
 * 			IACTV_TERM		The prompt was terminated through another signal.
 * 			IACTV_EOF		The prompt exited by encountered end-of-file.
 * @note	msh->exit will be set to EXIT_FAILURE if this function returns
 * 			IACTV_INTERRUPT or IACTV_TERM.
 */
int	prompt(t_promptf promptf, t_fd outf, char const *delim, t_msh *msh)
{
	pid_t const	pid = fork();
	int			wstat;

	if (pid == -1)
		return (msh_perror(0), IACTV_FAIL);
	if (pid == 0)
		promptf(outf, delim, msh);
	waitpid(pid, &wstat, 0);
	if (WIFSIGNALED(wstat))
	{
		msh->exit = EXIT_FAILURE;
		newline();
		if (WTERMSIG(wstat) == SIGINT)
			return (IACTV_INTERRUPT);
		return (IACTV_TERM);
	}
	return (WEXITSTATUS(wstat));
}

static inline void	newline(void)
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
