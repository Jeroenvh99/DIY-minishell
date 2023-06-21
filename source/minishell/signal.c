/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:33:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/13 15:33:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#include <stdio.h>
#include "readline/readline.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

extern struct s_g_msh	g_msh;

void	handler_set(int signum, t_handler handler)
{
	struct sigaction const	act = {.sa_handler = handler};

	sigaction(signum, &act, NULL);
}

void	handle_sigint(int signum)
{
	(void) signum;
	g_msh.exit = EXIT_FAILURE;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_sigint_heredoc(int signum)
{
	(void) signum;
	g_msh.exit = EXIT_FAILURE;
	write(STDERR_FILENO, "\n", 1);
}

void	handle_relay(int signum)
{
	kill(g_msh.child, signum);
}
