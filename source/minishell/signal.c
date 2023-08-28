/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:33:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/28 15:24:09 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#ifdef __APPLE__
# include <stdio.h>
#endif

#include "readline/readline.h"
#include <signal.h>
#include <unistd.h>

extern int	g_signum;

void	handler_set(int signum, t_handler handler)
{
	struct sigaction const	act = {.sa_handler = handler};

	sigaction(signum, &act, NULL);
}

void	handle_sigint(int signum)
{
	g_signum = signum;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_sigint_heredoc(int signum)
{
	g_signum = signum;
	write(STDERR_FILENO, "\n", 1);
}

void	handle_relay(int signum)
{
	g_signum = signum;
	write(STDERR_FILENO, "\n", 1);
}
