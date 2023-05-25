/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:27:41 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/25 11:40:47 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
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
		if (ft_dprintf(cmd->io.out, "%s\n", buf) == -1)
			return (-1);
		free(buf);
		return (0);
	}
	else
		return (1);
}

// int main(int argc, char **argv)
// {
// 	msh_pwd(argc, argv);
// }