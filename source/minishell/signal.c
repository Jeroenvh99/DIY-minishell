/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:33:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/01 12:38:44 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#include <signal.h>

extern int	g_signum;

void	handler_set(int signum, t_handler handler)
{
	struct sigaction const	act = {.sa_handler = handler};

	sigaction(signum, &act, NULL);
}
