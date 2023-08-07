/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:27:41 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/07 14:22:30 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
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
		if (printf("%s\n", buf) == -1)
			return (-1);
		free(buf);
		return (0);
	}
	else
		return (1);
}
