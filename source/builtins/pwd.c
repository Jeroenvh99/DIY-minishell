/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:27:41 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/29 10:29:33 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_stdio.h"
#include <stdlib.h>
#include <unistd.h>

int	msh_pwd(t_cmd *cmd, t_msh *msh)
{
	char	*buf;

	(void)msh;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		ft_dprintf(cmd->io[1], "%s\n", buf);
		free(buf);
		return (0);
	}
	else
		return (1);
}
