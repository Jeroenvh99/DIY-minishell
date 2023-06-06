/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:33:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/06 22:32:05 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>

extern t_msh	*g_msh;

void	handle_sigint(int signum)
{
	(void) signum;
	g_msh->exit = EXIT_FAILURE;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_heredoc(int signum)
{
	(void) signum;
}

void	handle_sigint_relay(int signum)
{
	kill(g_msh->child, signum);
}
