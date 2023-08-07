/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:27:41 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/07 16:53:28 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	msh_pwd(t_cmd *cmd, t_msh *msh)
{
	char	*buf;

	(void)msh;
	(void)cmd;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
		return (0);
	}
	else
		return (1);
}
