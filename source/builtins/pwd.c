/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:27:41 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/23 13:29:35 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <stdlib.h>
#include <unistd.h>

int	msh_pwd(t_cmd *cmd, t_msh *msh)
{
	char	*buf;

	(void)cmd;
	(void)msh;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		write(1, buf, ft_strlen(buf));
		free(buf);
		return (0);
	}
	else
		return (1);
}

int main(int argc, char **argv)
{
	msh_pwd(argc, argv);
}